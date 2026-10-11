"""Compile selected actual Markdown snippets and check against small oracles."""
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


def snippet(title):
    md = (ROOT / "模板.md").read_text("utf-8")
    start = md.index("\n## " + title + "\n")
    body = md[start:].split("\n## ", 2)[1]
    return re.search(r"```[^\n]*\n(.*?)```", body, re.S).group(1)


@unittest.skipUnless(shutil.which("g++"), "g++ is required")
class AlgorithmTests(unittest.TestCase):
    def run_cpp(self, code, data=""):
        with tempfile.TemporaryDirectory() as directory:
            base = Path(directory)
            src, exe = base / "test.cpp", base / "test.exe"
            src.write_text(code, "utf-8")
            build = subprocess.run(["g++", "-std=c++17", "-O2", str(src), "-o", str(exe)], capture_output=True, text=True)
            self.assertEqual(build.returncode, 0, build.stderr)
            result = subprocess.run([str(exe)], input=data, capture_output=True, text=True, timeout=10)
            self.assertEqual(result.returncode, 0, result.stderr)
            return result.stdout

    def wrapped(self, title, main, before="", after=""):
        return self.run_cpp("#include <bits/stdc++.h>\nusing namespace std; using ll=long long;\n" + before + snippet(title) + after + "\nint main(){" + main + "}")

    def test_block_query_does_not_count_left_block_twice(self):
        self.assertEqual(self.run_cpp(snippet("分块"), "9\n1 2 3 4 5 6 7 8 9\n2\n0 2 6 1\n0 2 9 5\n"), "5\n5\n")

    def test_sparse_table_max_and_both_searches(self):
        self.wrapped("ST表", '''mt19937 rng(42);
        for(int n=1;n<=35;n++){ vector<int>a(n);for(int &x:a)x=int(rng()%21)-10; ST<int>s(a);
        for(int l=0;l<n;l++)for(int r=l;r<n;r++)assert(s.query(l,r)==*max_element(a.begin()+l,a.begin()+r+1));
        for(int l=0;l<n;l++)for(int x=-11;x<=11;x++){int want=-1;for(int r=l;r<n;r++)if(a[r]>=x){want=r;break;}
        assert(s.find(l,x)==want);assert(s.find_binary_lifting(l,x)==want);}}''')

    def test_segment_tree_negative_values_and_right_search(self):
        self.wrapped("线段树", '''segmentTree<Info> s(vector<Info>{Info(-5),Info(-4),Info(-3),Info(-2)});
        assert(s.query(0,2)==-3); auto pred=[](Info a){return a.mx>=-4;};
        assert(s.findFirst(1,0,4,0,4,pred).first==1);assert(s.findLast(1,0,4,0,4,pred).first==3);
        assert(s.findLast(1,0,4,0,3,pred).first==2);s.modify(3,-9);assert(s.query(0,3)==-3);
        segmentTree<Info> empty;''')

    def test_weighted_dsu_repeated_merge_and_query_compress(self):
        self.wrapped("带权并查集", '''DSU d(4);d.merge(1,2);d.merge(3,1);d.merge(4,3);d.merge(4,1);
        assert(d.query(4,2)==2);assert(d.query(1,3)==0);assert(d.query(2,2)==0);assert(d.siz[d.find(2)]==4);''')

    def test_rectangular_matrix_product(self):
        self.wrapped("矩阵快速幂", '''matrix a{{1,2,3},{4,5,6}},b{{7,8},{9,10},{11,12}};
        auto c=a*b;assert(c.size()==2&&c[0].size()==2);assert(c[0][0]==58&&c[1][1]==154);
        assert(qpow(matrix{{2}},0)[0][0]==1);''', before="ll add(ll a,ll b){return (a+b)%1000000007;} ll mul(ll a,ll b){return a*b%1000000007;}\n")

    def test_combination_initialization_and_invalid_k(self):
        self.wrapped("排列组合数", '''init_comb(20);assert(C(5,2)==10);assert(P(5,2)==20);
        assert(C(0,0)==1);assert(C(0,1)==0);assert(C(5,-1)==0);assert(P(2,3)==0);''', before="const ll MOD=998244353; ll qpow(ll a,ll b=MOD-2){ll r=1;for(;b;b>>=1,a=a*a%MOD)if(b&1)r=r*a%MOD;return r;}\n")

    def test_digit_dp_including_zero_and_negative_prefix(self):
        self.assertEqual(self.run_cpp(snippet("数位DP"), "0 0\n"), "1\n")

    def test_tree_dp_reconstructs_descendants(self):
        self.assertEqual(self.run_cpp(snippet("树形DP"), "4\n1 2 4\n2 3 5\n3 4 6\n").split(), ["YES", "1", "3", "2", "4"])

    def test_kmp_overlapping_matches(self):
        self.assertEqual(self.run_cpp(snippet("KMP算法"), "aaaa aa\n").split(), ["1", "2", "3", "0", "1"])

    def test_ordinary_dsu_can_be_used_by_kruskal(self):
        self.wrapped("并查集", '''dsu d(6);d.merge(1,2);d.merge(3,4);d.merge(2,4);
        assert(d.same(1,3));assert(!d.same(1,5));assert(d.siz[d.find(1)]==4);''')

    def test_linear_sieve_factorization_is_callable(self):
        self.wrapped("线性筛", '''auto p=sieve(50);assert(p.size()==15);
        auto c=factorize(48);assert(c.size()==2&&c[2]==4&&c[3]==1);assert(factorize(1).empty());''')

    def test_random_graph_has_requested_root_offset(self):
        code = snippet("随机图")
        self.run_cpp('''#include <bits/stdc++.h>
        using namespace std; mt19937_64 rng(42);
        int Rand(int l,int r){return l;}\n''' + code + '''
        int main(){auto e=Graph(2,-1,1);assert(e.size()==1);assert(e[0][0]==2&&e[0][1]==1);}''')

    def test_fft_negative_and_constant_coefficients(self):
        self.wrapped("多项式", '''auto a=Poly{-3}*Poly{2};assert(a==Poly{-6});
        auto b=Poly{1,-2,3}*Poly{-2,4};assert((b==Poly{-2,8,-14,12}));''', before="using db=double;\n")

    def test_ntt_norm_one(self):
        self.wrapped("NTT（数论变换）", '''assert(Polynomial::norm(1)==1);
        Poly a{3},b{5};assert((a*b==Poly{15}));''')

    def test_trees_with_same_source_and_sink_have_no_flow(self):
        self.wrapped("最大流", '''static Flow f;f.add_edge(1,1,3);f.add_edge(1,2,4);
        assert(f.dicnic(1,1)==0);assert(f.dicnic(1,2)==4);''', before="const int N=10;\n")

    def test_frequency_tree_kth_largest_uses_counts(self):
        self.wrapped("权值线段树", '''a[1]=2;a[2]=1;a[4]=3;build(1,1,4);
        int want[]={4,4,4,2,1,1};for(int k=1;k<=6;k++)assert(kth(1,1,4,k)==want[k-1]);''', before="int a[10]{},tree[40]{};\n")

    def test_standalone_fft_negative_constant_product(self):
        self.wrapped("FFT（快速傅里叶变换）", '''auto a=Poly{-3}*Poly{2};assert(a==Poly{-6});''')


if __name__ == "__main__":
    unittest.main()
