#!/usr/bin/env python3
"""模板.md -> 完整 Markdown 内容 -> XeLaTeX 双栏手册。

运行 python make.py；仅生成 TeX：python make.py --no-pdf。
无需 Python 第三方包；编译需要 XeLaTeX (MiKTeX / TeX Live)。
"""
import argparse
from dataclasses import dataclass
from datetime import date
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile

BASE = Path(__file__).resolve().parent

PREAMBLE = r'''\documentclass[a4paper,9pt]{extarticle}
\usepackage[UTF8]{ctex}
\usepackage[top=16mm,bottom=14mm,left=12mm,right=12mm,columnsep=7mm]{geometry}
\usepackage{fancyhdr,titlesec,xcolor,amsmath,amssymb,listings,graphicx}
\usepackage{needspace,tabularx,array,booktabs}
\usepackage[colorlinks=true,linkcolor=accent,urlcolor=accent,bookmarksnumbered=true]{hyperref}
\definecolor{accent}{HTML}{24485D}
\definecolor{codebg}{HTML}{F5F7F8}
\definecolor{muted}{HTML}{61717B}
\IfFontExistsTF{Times New Roman}{\setmainfont{Times New Roman}}{}
\IfFontExistsTF{Arial}{\setsansfont{Arial}}{}
\IfFontExistsTF{Consolas}{\setmonofont{Consolas}[Scale=0.9]}{\setmonofont{Latin Modern Mono}}
\lstset{language=C++,basicstyle=\fontsize{7.6}{9.2}\selectfont\ttfamily,
  keywordstyle=\bfseries\color{accent},commentstyle=\color{muted},
  stringstyle=\color{black!80},numbers=left,numberstyle=\fontsize{5.5}{7}\selectfont\color{muted},
  numbersep=5pt,backgroundcolor=\color{codebg},
  showspaces=false,showstringspaces=false,showtabs=false,tabsize=2,
  columns=flexible,keepspaces=true,breaklines=true,breakatwhitespace=false,
  breakindent=1em,
  frame=l,framerule=0.4pt,rulecolor=\color{accent!35},framesep=3pt,
  aboveskip=5pt,belowskip=5pt,xleftmargin=10pt,xrightmargin=3pt}
\pagestyle{fancy}\fancyhf{}
\fancyhead[L]{\fontsize{8}{10}\selectfont\sffamily\color{muted}ACM / ICPC}
\fancyhead[R]{\fontsize{8}{10}\selectfont\sffamily\color{muted}\leftmark}
\fancyfoot[C]{\fontsize{8}{10}\selectfont\sffamily\thepage}
\renewcommand{\sectionmark}[1]{\markboth{#1}{}}
\renewcommand{\headrulewidth}{0.3pt}\setlength{\headheight}{13pt}
\titleformat{\section}{\large\bfseries\sffamily\color{accent}}{\thesection}{0.6em}{}[\titlerule]
\titleformat{\subsection}{\normalsize\bfseries\sffamily\color{accent}}{\thesubsection}{0.5em}{}
\titleformat{\subsubsection}{\small\bfseries}{\thesubsubsection}{0.5em}{}
\titlespacing*{\section}{0pt}{10pt}{5pt}
\titlespacing*{\subsection}{0pt}{8pt}{3pt}
\titlespacing*{\subsubsection}{0pt}{5pt}{2pt}
\setcounter{tocdepth}{2}\setcounter{secnumdepth}{2}
\setlength{\parindent}{0pt}\setlength{\parskip}{2.5pt}
\setlength{\emergencystretch}{2em}
\raggedbottom
\newsavebox{\mathbox}
\newcommand{\fitmath}[1]{\par\smallskip\begingroup
  \sbox{\mathbox}{$\displaystyle #1$}
  \noindent\makebox[\linewidth][c]{\ifdim\wd\mathbox>\linewidth
    \resizebox{\linewidth}{!}{\usebox{\mathbox}}\else\usebox{\mathbox}\fi}
  \par\endgroup\smallskip}
\hypersetup{pdftitle={ACM/ICPC 算法模板},pdfauthor={Rejected}}
\begin{document}
'''


@dataclass
class Block:
    kind: str
    text: str
    level: int = 0
    language: str = ""


def parse_markdown(source):
    """Preserve source order; reject unterminated code/math instead of losing it."""
    lines = source.splitlines()
    blocks = []
    i = 0
    while i < len(lines):
        line = lines[i]
        stripped = line.strip()
        fence = re.fullmatch(r"(`{3,}|~{3,})(.*)", stripped)
        if fence:
            delimiter, language = fence.groups()
            content = []
            i += 1
            closing = re.escape(delimiter[0]) + "{" + str(len(delimiter)) + r",}\s*"
            while i < len(lines) and not re.fullmatch(closing, lines[i].strip()):
                content.append(lines[i])
                i += 1
            if i == len(lines):
                raise ValueError("代码围栏未闭合")
            blocks.append(Block("code", "\n".join(content), language=language.strip().split(" ")[0]))
        elif stripped == "$$":
            content = []
            i += 1
            while i < len(lines) and lines[i].strip() != "$$":
                if lines[i].strip():
                    content.append(lines[i])
                i += 1
            if i == len(lines):
                raise ValueError("数学公式 $$ 未闭合")
            blocks.append(Block("math", "\n".join(content)))
        elif stripped.startswith("$$") and stripped.endswith("$$") and len(stripped) > 4:
            blocks.append(Block("math", stripped[2:-2]))
        elif match := re.match(r"^(#{1,6})\s+(.+)$", line):
            blocks.append(Block("heading", match[2], len(match[1])))
        elif stripped.startswith("|") and i + 1 < len(lines) and re.fullmatch(r"\|?[\s:|\-]+\|?", lines[i + 1].strip()):
            content = [line]
            i += 2
            while i < len(lines) and lines[i].strip().startswith("|"):
                content.append(lines[i])
                i += 1
            blocks.append(Block("table", "\n".join(content)))
            continue
        elif re.fullmatch(r"(?:-{3,}|\*{3,}|_{3,})", stripped):
            blocks.append(Block("rule", ""))
        elif stripped:
            blocks.append(Block("text", line))
        else:
            blocks.append(Block("blank", ""))
        i += 1
    return blocks


def esc(text):
    # One pass: inserted TeX braces/backslashes must not be re-escaped.
    replacements = {"\\": r"\textbackslash{}", "#": r"\#", "%": r"\%",
                    "&": r"\&", "_": r"\_", "{": r"\{", "}": r"\}",
                    "$": r"\$", "~": r"\textasciitilde{}", "^": r"\textasciicircum{}"}
    return "".join(replacements.get(ch, ch) for ch in text)


def inline(text):
    """Keep formulas; safely format Markdown emphasis, inline code and links."""
    parts = re.split(r"(`[^`]+`|\$[^$\n]+\$|\*\*[^*]+\*\*|\[[^\]]+\]\([^)]+\))", text)
    rendered = []
    for part in parts:
        if part.startswith("`") and part.endswith("`"):
            rendered.append(r"\texttt{" + breakable_esc(part[1:-1]) + "}")
        elif part.startswith("$") and part.endswith("$"):
            rendered.append(part)
        elif part.startswith("**") and part.endswith("**"):
            rendered.append(r"\textbf{" + inline(part[2:-2]) + "}")
        elif match := re.fullmatch(r"\[([^\]]+)\]\(([^)]+)\)", part):
            rendered.append(r"\href{" + esc(match[2]) + "}{" + inline(match[1]) + "}")
        else:
            rendered.append(breakable_esc(part))
    return "".join(rendered)


def breakable_esc(text):
    """Allow long C++ expressions/paths in narrow columns to wrap at punctuation."""
    out = []
    for token in re.split(r"(\s+)", text):
        if len(token) <= 12 and "/" not in token:
            out.append(esc(token))
            continue
        for i, ch in enumerate(token):
            out.append(esc(ch))
            if ch in "_/.(),+-:;=<>" and i + 1 < len(token) and token[i + 1].isascii():
                out.append(r"\allowbreak{}")
    return "".join(out)


def render_block(block, intro=False):
    if block.kind == "heading":
        if intro and block.level == 1:
            return ""
        command = {1: "section", 2: "subsection", 3: "subsubsection"}.get(block.level, "paragraph")
        title = inline(block.text)
        if "$" in block.text:
            title = r"\texorpdfstring{" + title + "}{" + esc(block.text.replace("$", "")) + "}"
        return r"\Needspace{5\baselineskip}" + "\n\\" + command + ("*" if intro else "") + "{" + title + "}"
    if block.kind == "code":
        language = {"cpp": "C++", "c++": "C++", "c": "C", "python": "Python", "py": "Python", "java": "Java"}.get(block.language.lower(), "")
        return "\\begin{lstlisting}[language={" + language + "}]\n" + block.text + "\n\\end{lstlisting}"
    if block.kind == "math":
        return "\\fitmath{\n" + block.text + "\n}"
    if block.kind == "table":
        rows = [[cell.strip() for cell in row.strip().strip("|").split("|")] for row in block.text.splitlines()]
        columns = len(rows[0])
        if any(len(row) != columns for row in rows):
            raise ValueError("表格各行列数不一致")
        out = [r"\par\smallskip{\footnotesize\renewcommand{\arraystretch}{1.3}",
               r"\begin{tabularx}{\linewidth}{@{}" + ">{\\raggedright\\arraybackslash}X" * columns + "@{}}", r"\toprule"]
        for i, row in enumerate(rows):
            out.append(" & ".join(inline(cell) for cell in row) + r" \\")
            if i == 0:
                out.append(r"\midrule")
        out.extend([r"\bottomrule", r"\end{tabularx}}\par\smallskip"])
        return "\n".join(out)
    if block.kind == "rule":
        return r"\par\smallskip"
    if block.kind == "blank":
        return ""
    text = block.text.strip()
    if text.startswith("> "):
        return r"{\small\color{muted}" + inline(text[2:]) + r"}\par"
    if re.match(r"^[-*]\s+", text):
        return r"\noindent\textbullet\enspace " + inline(text[2:]) + r"\par"
    return inline(text)


def render_cover():
    """A vector cover; independent of Markdown maintenance instructions."""
    logo_path = BASE / "assets" / "icpc-foundation.pdf"
    logo = (r"\includegraphics[width=56mm]{\detokenize{" + logo_path.as_posix() + "}}"
            if logo_path.is_file() else r"{\fontsize{24}{28}\selectfont\sffamily\bfseries\color{accent}ICPC}")
    return r'''\thispagestyle{empty}
\setlength{\unitlength}{1mm}
\noindent\begin{picture}(186,255)
\put(0,204){''' + logo + r'''}
\put(0,177){\makebox(0,0)[l]{\fontsize{47}{52}\selectfont\sffamily\bfseries\color{accent}ICPC / ACM}}
\put(0,157){\makebox(0,0)[l]{\fontsize{25}{30}\selectfont\sffamily\bfseries\color{accent}算法模板手册}}
\put(0,142){\makebox(0,0)[l]{\fontsize{10}{14}\selectfont\sffamily\color{muted}COMPETITIVE PROGRAMMING NOTEBOOK}}
\put(0,132){\color{accent}\rule{186mm}{0.5pt}}
{\color{accent!18}\linethickness{0.55pt}
\qbezier(70,63)(85,81)(100,99)
\qbezier(100,99)(124,96)(148,93)
\qbezier(148,93)(164,78)(180,63)
\qbezier(70,63)(97,62)(124,61)
\qbezier(100,99)(112,80)(124,61)
\qbezier(124,61)(136,77)(148,93)
\qbezier(124,61)(152,62)(180,63)
\qbezier(100,99)(103,113)(106,127)
\qbezier(148,93)(166,107)(184,121)
\qbezier(148,93)(127,110)(106,127)
\put(70,63){\circle{5}}\put(124,61){\circle{5}}
\put(180,63){\circle{5}}\put(106,127){\circle{5}}
\put(184,121){\circle{5}}}
\put(100,99){\color[rgb]{0.298,0.510,0.765}\circle*{5}}
\put(148,93){\color[rgb]{0.992,0.729,0.067}\circle*{5}}
\put(124,61){\color[rgb]{0.698,0.176,0.106}\circle*{5}}
\put(0,29){\makebox(0,0)[l]{\fontsize{13}{17}\selectfont\sffamily\bfseries\color{accent}Rejected}}
\put(0,19){\makebox(0,0)[l]{\fontsize{9}{12}\selectfont\sffamily\color{muted}''' + date.today().isoformat() + r'''}}
\end{picture}
'''


def generate_tex(source):
    blocks = parse_markdown(source)
    first_section = next((i for i, b in enumerate(blocks) if b.kind == "heading" and b.level == 1 and b.text != "ACM/ICPC 算法模板"), len(blocks))
    intro, body = blocks[:first_section], blocks[first_section:]
    sections = sum(b.kind == "heading" and b.level == 1 for b in body)
    entries = sum(b.kind == "heading" and b.level == 2 for b in body)
    codes = sum(b.kind == "code" for b in body)
    out = [PREAMBLE, render_cover()]
    # Keep future introductory content on its own page, never on the cover.
    if any(b.kind not in {"blank", "rule"} and not (b.kind == "heading" and b.level == 1) for b in intro):
        out.append(r"\clearpage")
        out.extend(render_block(b, intro=True) for b in intro)
    out.extend([r"\clearpage\twocolumn", r"\tableofcontents", r"\clearpage"])
    out.extend(render_block(b) for b in body)
    out.append(r"\end{document}")
    return "\n".join(out), (sections, entries, codes)


def find_engine(explicit=None):
    requested = explicit or os.environ.get("XELATEX")
    if requested:
        path = shutil.which(requested) or (requested if Path(requested).is_file() else None)
        if not path:
            raise FileNotFoundError(f"找不到 XeLaTeX：{requested}")
        return path
    path = shutil.which("xelatex")
    if path:
        return path
    fallback = Path(os.environ.get("LOCALAPPDATA", "")) / "Programs/MiKTeX/miktex/bin/x64/xelatex.exe"
    if fallback.is_file():
        return str(fallback)
    raise FileNotFoundError("未找到 XeLaTeX。请安装 MiKTeX / TeX Live，或使用 --engine 指定路径。")


def compile_pdf(tex_path, pdf_path, engine):
    """Only replace the user's PDF after all compilation passes succeed."""
    with tempfile.TemporaryDirectory(prefix=".acm-build-", dir=tex_path.parent) as directory:
        build_dir = Path(directory)
        for pass_number in range(1, 4):
            print(f"XeLaTeX pass {pass_number}/3...", flush=True)
            result = subprocess.run([engine, "-no-shell-escape", "-halt-on-error", "-interaction=nonstopmode",
                                     f"-output-directory={build_dir}", str(tex_path)],
                                    cwd=build_dir, capture_output=True, timeout=300)
            output = result.stdout.decode("utf-8", errors="replace")
            log = build_dir / (tex_path.stem + ".log")
            if log.exists():
                shutil.copy2(log, tex_path.with_suffix(".log"))
            if result.returncode != 0:
                raise RuntimeError("XeLaTeX 编译失败；原 PDF 已保留。详见 " + str(tex_path.with_suffix(".log")) + "\n" + output[-3000:])
        built_pdf = build_dir / (tex_path.stem + ".pdf")
        if not built_pdf.is_file() or built_pdf.stat().st_size == 0:
            raise RuntimeError("编译器没有输出 PDF；原 PDF 已保留。")
        try:
            shutil.copy2(built_pdf, pdf_path)
        except PermissionError:
            # PDF viewers on Windows may lock the destination. Keep the new
            # result instead of losing a successful build during temp cleanup.
            alternative = pdf_path.with_name(pdf_path.stem + "_新版.pdf")
            try:
                shutil.copy2(built_pdf, alternative)
            except PermissionError:
                alternative = pdf_path.with_name(pdf_path.stem + "_新版_" + str(os.getpid()) + ".pdf")
                shutil.copy2(built_pdf, alternative)
            pdf_path = alternative
            print(f"原 PDF 无法覆盖，已另存：{pdf_path}")
        for suffix in (".aux", ".toc", ".out"):
            source = build_dir / (tex_path.stem + suffix)
            if source.exists():
                shutil.copy2(source, tex_path.with_suffix(suffix))
    return pdf_path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--input", type=Path, default=BASE / "模板.md")
    parser.add_argument("--output", type=Path, default=BASE / "acm_template.pdf")
    parser.add_argument("--engine", help="XeLaTeX 可执行文件路径；也可设置 XELATEX 环境变量")
    parser.add_argument("--no-pdf", action="store_true", help="仅生成 .tex，保留已有 PDF")
    args = parser.parse_args()
    pdf_path = args.output.resolve()
    tex_path = pdf_path.with_suffix(".tex")
    tex, (sections, entries, codes) = generate_tex(args.input.read_text(encoding="utf-8-sig"))
    tex_path.parent.mkdir(parents=True, exist_ok=True)
    tex_path.write_text(tex, encoding="utf-8")
    print(f"{sections} sections / {entries} entries / {codes} code blocks -> {tex_path}")
    if not args.no_pdf:
        pdf_path = compile_pdf(tex_path, pdf_path, find_engine(args.engine))
        print(f"DONE: {pdf_path} ({pdf_path.stat().st_size // 1024} KB)")


if __name__ == "__main__":
    try:
        main()
    except (OSError, ValueError, RuntimeError, subprocess.TimeoutExpired) as error:
        raise SystemExit(str(error)) from error
