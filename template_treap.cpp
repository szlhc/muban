/*
Treap，一种数据结构，支持插入节点、删除节点、求第x大的节点、求权值为x的节点的排名、求权值比x小的最大节点、求权值比x大的最小节点
*/

#include <cstdio>
#include <cstdlib>

const int N = 1e5+5;
const int INF = 1<<30;

struct treap {
  //ls rs左儿子 右儿子节点. val值,rnd 随机权重(用于平衡),size 该节点树节点个数,w该节点值个数
  int ls[N], rs[N], val[N], rnd[N], size[N], w[N];
  int sz, ans, rt;//sz 总节点, ans, rt root根节点

  //更新k子树节点个数
  inline void pushup(int x) { size[x] = size[ls[x]] + size[rs[x]] + w[x]; }
  //左旋 理解为讲k的右儿子绕着k向左旋转.
  //1. 将k的放到k的左儿子
  //2. 将原k的右儿子放入k原来位置
  //3. 将原k的右儿子的左子树放到k的右子树
  void lrotate(int &k) {
    int t = rs[k];//保存k节点右儿子编号
    rs[k] = ls[t];//k的右儿子的左子树放到k的右子树
    ls[t] = k;//将k放到原k节点的右儿子的左子树
    size[t] = size[k];//更新t的节点个数
    pushup(k);//
    k = t;
  }
  void rrotate(int &k) {
    int t = ls[k];
    ls[k] = rs[t];
    rs[t] = k;
    size[t] = size[k];
    pushup(k);
    k = t;
  }
  //插入 
  void insert(int &k, int x) {
    if (!k) {
      sz++;//节点个数增加
      k = sz;//节点序号
      size[k] = 1;
      w[k] = 1;
      val[k] = x;
      rnd[k] = rand();
      return;
    }
    size[k]++;//子树节点个数
    if (val[k] == x) {
      w[k]++;
    } else if (val[k] < x) {
      insert(rs[k], x); 
      //如果右子树权重 < 左子树权重 左旋
      if (rnd[rs[k]] < rnd[k]) lrotate(k);
    } else {
      insert(ls[k], x);
      if (rnd[ls[k]] < rnd[k]) rrotate(k);
    }
  }

  void del(int &k, int x) {
    if (!k) return;
    if (val[k] == x) {
      if (w[k] > 1) {
        w[k]--;
        size[k]--;
        return;
      }
      if (ls[k] == 0 || rs[k] == 0)//链或空
        k = ls[k] + rs[k];//把子节点代替k
      //旋转至底部再删除
      else if (rnd[ls[k]] < rnd[rs[k]]) {
        rrotate(k);
        del(k, x);
      } else {
        lrotate(k);
        del(k, x);
      }
    } else if (val[k] < x) {
      size[k]--;
      del(rs[k], x);
    } else {
      size[k]--;
      del(ls[k], x);
    }
  }
  //查询x的排名
  int queryrank(int k, int x) {
    if (!k) return 0;
    if (val[k] == x)
      return size[ls[k]] + 1;
    else if (x > val[k]) 
      return size[ls[k]] + w[k] + queryrank(rs[k], x);
    else
      return queryrank(ls[k], x);
  }
  //查询排序为x的数
  int querynum(int k, int x) {
    if (!k) return 0;
    if (x <= size[ls[k]])
      return querynum(ls[k], x);
    else if (x > size[ls[k]] + w[k])
      return querynum(rs[k], x - size[ls[k]] - w[k]);
    else
      return val[k];
  }
  //前驱
  void querypre(int k, int x) {
    if (!k) return;
    if (val[k] < x)
      ans = k, querypre(rs[k], x);
    else
      querypre(ls[k], x);
  }
  //后继
  void querysub(int k, int x) {
    if (!k) return;
    if (val[k] > x)
      ans = k, querysub(ls[k], x);
    else
      querysub(rs[k], x);
  }
} T;

int main() 
{
  srand(123);
  int n;
  scanf("%d", &n);
  int opt, x;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &opt, &x);
    if (opt == 1)
      T.insert(T.rt, x);
    else if (opt == 2)
      T.del(T.rt, x);
    else if (opt == 3) {
      printf("%d\n", T.queryrank(T.rt, x));
    } else if (opt == 4) {
      printf("%d\n", T.querynum(T.rt, x));
    } else if (opt == 5) {
      T.ans = 0;
      T.querypre(T.rt, x);
      printf("%d\n", T.val[T.ans]);
    } else if (opt == 6) {
      T.ans = 0;
      T.querysub(T.rt, x);
      printf("%d\n", T.val[T.ans]);
    }
  }
  return 0;
}
