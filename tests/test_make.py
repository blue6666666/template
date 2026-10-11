"""Regression tests for lost Markdown content; no TeX installation needed."""
import contextlib
import io
from pathlib import Path
import runpy
import sys
import tempfile
import unittest
from unittest.mock import patch
from types import SimpleNamespace

ROOT = Path(__file__).resolve().parents[1]


def generate(markdown):
    with tempfile.TemporaryDirectory() as directory:
        base = Path(directory)
        (base / "make.py").write_text((ROOT / "make.py").read_text("utf-8"), "utf-8")
        (base / "模板.md").write_text(markdown, "utf-8")
        with patch.object(sys, "argv", ["make.py", "--no-pdf"]), \
             patch("subprocess.run", return_value=SimpleNamespace(stdout="", returncode=0)), \
             contextlib.redirect_stdout(io.StringIO()):
            runpy.run_path(str(base / "make.py"), run_name="__main__")
        return (base / "acm_template.tex").read_text("utf-8")


class MarkdownTests(unittest.TestCase):
    def test_all_code_blocks_and_text_after_code_survive(self):
        tex = generate("# 数据结构\n## 算法\n用法说明\n```cpp\nint first;\n```\n后续说明\n```python\nprint('second')\n```\n")
        for text in ["int first;", "print('second')", "用法说明", "后续说明"]:
            self.assertIn(text, tex)

    def test_formula_only_entry_and_table_survive(self):
        tex = generate("# 数学\n## 纯公式\n$$\n\\binom{n}{k}\n$$\n| 形式 | 结果 |\n|---|---|\n| $x^2$ | $y$ |\n")
        for text in ["纯公式", r"\binom{n}{k}", "x^2", "结果"]:
            self.assertIn(text, tex)

    def test_heading_inside_fence_is_never_a_section(self):
        tex = generate("# 数学\n## 示范\n```python\n# 注释\nprint(1)\n```\n")
        self.assertIn("# 注释", tex)
        self.assertNotIn(r"\section{注释}", tex)

    def test_tex_special_characters_are_escaped_once(self):
        tex = generate("# 数学\n## A_B & C\n路径 `a_b\\c` 与 50%\n```cpp\nint x;\n```\n")
        self.assertIn(r"A\_B \& C", tex)
        self.assertIn(r"50\%", tex)
        self.assertNotIn(r"\textbackslash\{\}", tex)

    def test_compiler_failure_preserves_previous_pdf(self):
        sys.path.insert(0, str(ROOT))
        import make
        with tempfile.TemporaryDirectory() as directory:
            base = Path(directory)
            tex, pdf = base / "book.tex", base / "book.pdf"
            tex.write_text("invalid tex", "utf-8")
            pdf.write_bytes(b"previous valid PDF")
            # Python is a real executable that rejects XeLaTeX's arguments.
            with self.assertRaises(RuntimeError):
                make.compile_pdf(tex, pdf, sys.executable)
            self.assertEqual(pdf.read_bytes(), b"previous valid PDF")

    def test_unclosed_fence_and_math_fail_explicitly(self):
        sys.path.insert(0, str(ROOT))
        import make
        for source in ["# 数学\n```cpp\nint x;", "# 数学\n$$\nx^2"]:
            with self.assertRaises(ValueError):
                make.generate_tex(source)


if __name__ == "__main__":
    unittest.main()
