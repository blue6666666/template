import os, re

BASE = r"E:\项目\模板"
output_path = os.path.join(BASE, "acm_template.tex")

PREAMBLE = r"""\documentclass[a4paper,9pt,twocolumn]{extarticle}
\usepackage[UTF8]{ctex}
\usepackage[top=1cm,bottom=1cm,left=1cm,right=1cm,columnsep=0.6cm]{geometry}
\usepackage{fancyhdr,titlesec,sectsty,xcolor,amsmath,amssymb,listings,flushend}
\usepackage[colorlinks=true,linkcolor=black,urlcolor=black,citecolor=black]{hyperref}
\setmainfont{Times New Roman}\setsansfont{Arial}\setmonofont{Consolas}[Scale=0.9]
\definecolor{codebg}{gray}{0.95}\definecolor{commentgreen}{gray}{0.45}
\lstset{language=C++,basicstyle=\fontsize{7.5}{9}\selectfont\ttfamily\color{black},
  keywordstyle=\bfseries\color{black},commentstyle=\itshape\color{commentgreen},
  stringstyle=\color{black},numbers=left,numberstyle=\tiny\color{gray},
  stepnumber=1,numbersep=4pt,backgroundcolor=\color{codebg},
  showspaces=false,showstringspaces=false,showtabs=false,tabsize=2,
  breaklines=true,breakatwhitespace=false,frame=single,framerule=0.3pt,
  rulecolor=\color{black!30},framesep=4pt,aboveskip=4pt,belowskip=4pt,
  lineskip=0.5pt,xleftmargin=4pt,xrightmargin=4pt}
\pagestyle{fancy}\fancyhf{}\fancyhead[L]{\small\sffamily\color{gray}\leftmark}
\fancyhead[R]{\small\sffamily\color{gray}\rightmark}\fancyfoot[C]{\small\sffamily\thepage}
\renewcommand{\headrulewidth}{0.3pt}\setlength{\headheight}{14pt}
\allsectionsfont{\sffamily}
\titleformat{\section}{\Large\bfseries\sffamily}{\thesection}{0.8em}{}[{\vspace{-0.3em}\titlerule[0.3pt]}]
\titleformat{\subsection}{\normalsize\bfseries\sffamily}{\thesubsection}{0.6em}{}
\titlespacing{\section}{0pt}{8pt}{4pt}\titlespacing{\subsection}{0pt}{6pt}{2pt}
\newcommand{\algo}[1]{\subsection{#1}}
\newcommand{\algodesc}[1]{\smallskip{\small\color{black!70}#1}\smallskip}
\begin{document}
\title{\Huge\bfseries\sffamily ACM/ICPC 算法模板}\author{\large The Three Stooges}\date{\today}\maketitle
\tableofcontents\newpage
"""

def parse_ll(filepath):
    with open(filepath, encoding='utf-8') as f: content = f.read()
    results = []
    sec = None; algo = None; sub = None; in_c = False; cl = []
    for line in content.split('\n'):
        if not in_c:
            m = re.match(r'^#\s+(.+)', line)
            if m and not line.strip().startswith('##'): sec = m.group(1).strip(); continue
            m = re.match(r'^##\s+(.+)', line)
            if m and not line.strip().startswith('###'): algo = m.group(1).strip(); sub = None; continue
            m = re.match(r'^###\s+(.+)', line)
            if m: sub = m.group(1).strip(); continue
        if line.strip().startswith('```'):
            if not in_c: in_c = True; cl = []; continue
            else:
                in_c = False
                code = '\n'.join(cl).strip()
                if code:
                    t = algo or ""
                    if sub: t = f"{t}: {sub}"
                    if sec and t and len(t) < 200: results.append((sec, t, code, ""))
                continue
        if in_c: cl.append(line)
    return results

def parse_std(filepath):
    with open(filepath, encoding='utf-8') as f: content = f.read()
    results = []
    sec = None; algo = None; in_c = False; cl = []
    for line in content.split('\n'):
        if not in_c:
            m = re.match(r'^##\s+(.+)', line)
            if m and not line.strip().startswith('###'): sec = m.group(1).strip(); continue
            m = re.match(r'^###\s+(.+)', line)
            if m: algo = m.group(1).strip(); continue
        if line.strip().startswith('```'):
            if not in_c: in_c = True; cl = []; continue
            else:
                in_c = False
                code = '\n'.join(cl).strip()
                if sec and algo and code: results.append((sec, algo, code, ""))
                algo = None; continue
        if in_c: cl.append(line)
    return results

def esc(s):
    for ch, rep in [('\\','\\textbackslash{}'),('#','\\#'),('%','\\%'),('&','\\&'),('_','\\_'),('{','\\{'),('}','\\}'),('$','\\$'),('~','\\textasciitilde{}'),('^','\\textasciicircum{}')]:
        s = s.replace(ch, rep)
    return s

SEC_MAP = {
    "赛前准备":"不要忘记","杂项":"不要忘记","不要忘记":"不要忘记",
    "数据结构":"数据结构","图论":"图论","数学":"数学",
    "字符串":"字符串","DP":"动态规划","计算几何":"计算几何",
    "图论算法":"图论","数论算法":"数学","字符串算法":"字符串",
    "其他算法":"其它","动态规划":"动态规划",
}

# 不要忘记放在最前面，然后按这个顺序
SECTION_ORDER = ["不要忘记","数据结构","图论","数学","字符串","动态规划","计算几何","其它"]

from collections import OrderedDict
all_algos = OrderedDict()
for sec in SECTION_ORDER: all_algos[sec] = []
seen = set()

# from littledrink
for s, t, c, d in parse_ll(os.path.join(BASE, "from littledrink.md")):
    ms = SEC_MAP.get(s, s)
    if ms not in all_algos: all_algos[ms] = []
    if t in seen: continue
    seen.add(t)
    all_algos[ms].append((t, c, d))

# original files
for fname in ["不要忘记.md","数据结构.md","图论.md","数论.md","字符串算法.md","动态规划.md","计算几何.md","其他.md"]:
    fp = os.path.join(BASE, fname)
    if not os.path.exists(fp): continue
    for s, t, c, d in parse_std(fp):
        ms = SEC_MAP.get(s, s)
        if ms not in all_algos: all_algos[ms] = []
        if t in seen: continue
        seen.add(t)
        all_algos[ms].append((t, c, d))

# Write
lines = [PREAMBLE]
for sec in SECTION_ORDER:
    algos = all_algos.get(sec, [])
    if not algos: continue
    lines.append(f"\\section{{{esc(sec)}}}\n")
    for t, c, d in algos:
        lines.append(f"\\algo{{{esc(t)}}}")
        if d: lines.append(f"\\algodesc{{{esc(d)}}}")
        lines.append("\\begin{lstlisting}")
        lines.append(c)
        lines.append("\\end{lstlisting}\n")

lines.append("\\end{document}")

out = '\n'.join(lines)
with open(output_path, 'w', encoding='utf-8') as f:
    f.write(out)

sec_summary = {s: len(all_algos.get(s,[])) for s in SECTION_ORDER}
print(f"Total: {len(seen)} algorithms, {len(out):,} bytes")
for s, n in sec_summary.items():
    if n > 0: print(f"  {s}: {n}")
