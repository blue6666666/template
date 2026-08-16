#!/usr/bin/env python3
"""make.py: 读取 模板.md → 生成 acm_template.tex → xelatex 编译 PDF"""
import os, re, subprocess
from collections import OrderedDict

BASE = os.path.dirname(os.path.abspath(__file__))
MIKTEX = r"C:\Users\14239\AppData\Local\Programs\MiKTeX\miktex\bin\x64\miktex-xetex.exe"
BT = chr(96); NL = chr(10); BS = chr(92)

PREAMBLE = r'''\documentclass[a4paper,9pt,twocolumn]{extarticle}
\usepackage[UTF8]{ctex}
\usepackage[top=1cm,bottom=1cm,left=1cm,right=1cm,columnsep=0.6cm]{geometry}
\usepackage{fancyhdr,titlesec,xcolor,amsmath,amssymb,listings}
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
\titleformat{\section}{\Large\bfseries\sffamily}{\thesection}{0.8em}{}[{\vspace{-0.3em}\titlerule[0.3pt]}]
\titleformat{\subsection}{\normalsize\bfseries\sffamily}{\thesubsection}{0.6em}{}
\titlespacing{\section}{0pt}{8pt}{4pt}\titlespacing{\subsection}{0pt}{6pt}{2pt}
\newcommand{\algo}[1]{\subsection{#1}}
\begin{document}
\title{\Huge\bfseries\sffamily ACM/ICPC}\author{\large The Three Stooges}\date{\today}\maketitle
\tableofcontents\newpage
'''

def esc(s):
    for ch, rp in [("\\", "\\textbackslash{}"), ("#", "\\#"), ("%", "\\%"),
                   ("&", "\\&"), ("_", "\\_"), ("{", "\\{"), ("}", "\\}"), ("$", "\\$")]:
        s = s.replace(ch, rp)
    return s

# ===== 1. 解析 模板.md =====
md_path = os.path.join(BASE, "模板.md")
with open(md_path, encoding="utf-8") as f:
    c = f.read()

sec = algo = None; ic = False; cl = []; algos = []
for l in c.split(NL):
    if not ic:
        m = re.match(r'^#\s+(.+)', l)
        if m and not l.strip().startswith('##'): sec = m.group(1).strip(); continue
        m = re.match(r'^##\s+(.+)', l)
        if m: algo = m.group(1).strip(); continue
    if l.strip().startswith(BT*3):
        if not ic: ic = True; cl = []; continue
        else:
            ic = False; code = NL.join(cl).strip()
            if sec and algo and code and sec not in ["ACM/ICPC 算法模板", "如何添加算法"]:
                algos.append((sec, algo, code))
            algo = None; continue
    if ic: cl.append(l)

grp = OrderedDict()
for s, t, c in algos:
    if s not in grp: grp[s] = []
    grp[s].append((t, c))

# ===== 2. 生成 .tex =====
lines = [PREAMBLE]
for sec, items in grp.items():
    lines.append(BS + "section{" + esc(sec) + "}" + NL)
    for t, c in items:
        lines.append(BS + "algo{" + esc(t) + "}")
        lines.append(BS + "begin{lstlisting}")
        lines.append(c)
        lines.append(BS + "end{lstlisting}" + NL)
lines.append(BS + "end{document}")

tex_path = os.path.join(BASE, "acm_template.tex")
with open(tex_path, "w", encoding="utf-8") as f:
    f.write(NL.join(lines))

total = sum(len(v) for v in grp.values())
print(f"模板.md -> {total} algorithms in {len(grp)} sections")

# ===== 3. 编译 PDF =====
for nm in ["acm_template.aux", "acm_template.log", "acm_template.out",
           "acm_template.toc", "acm_template.pdf"]:
    try: os.remove(os.path.join(BASE, nm))
    except: pass

for pn in [1, 2]:
    print(f"XeLaTeX pass {pn}...")
    r = subprocess.run([MIKTEX, "-fmt=xelatex", "-interaction=nonstopmode",
        "acm_template.tex"], cwd=BASE, capture_output=True, text=True, timeout=300)
    if "Output written" in r.stdout:
        print("  " + r.stdout.split("Output written")[1].split(NL)[0].strip())

pdf_path = os.path.join(BASE, "acm_template.pdf")
if os.path.exists(pdf_path):
    kb = os.path.getsize(pdf_path) // 1024
    print(f"DONE: acm_template.pdf ({kb} KB)")
else:
    print("FAILED")