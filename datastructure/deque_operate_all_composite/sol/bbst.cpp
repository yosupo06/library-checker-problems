
#include <vector>
#include <algorithm>
#include <utility>

using u32 = unsigned int;
using u64 = unsigned long long;

const u32 MOD = 998244353;

struct F{
    u32 a;
    u32 b;
    u32 z;

    u32 operator()(u32 x) const { return ((u64)x * a + b) % MOD; }
};

F operator+(F l, F r){
    F res;
    res.a = (u64)l.a * r.a % MOD;
    res.b = ((u64)l.b * r.a + r.b) % MOD;
    res.z = l.z + r.z;
    return res;
}


namespace nachia{

    template<
        class S,
        class F,
        S op(S l, S r),
        S e(),
        void reverseprod(S& x),
        S mapping(F f, S x),
        F composition(F f, F x),
        F id()
    >
    struct SplayTreeByIdx{
        static SplayTreeByIdx *NIL;

        using MyType = SplayTreeByIdx;

        MyType *l = nullptr;
        MyType *r = nullptr;
        MyType *p = nullptr;
        S a = e();
        S mprod = e();
        F f = id();
        bool propagated = true;
        int rev = 0;

        SplayTreeByIdx(){
        }

        void prepareDown(){
            if(!propagated){
                if(l != NIL){
                    l->a = mapping(f, l->a);
                    l->mprod = mapping(f, l->mprod);
                    l->f = composition(f, l->f);
                    l->propagated = false;
                }
                if(r != NIL){
                    r->a = mapping(f, r->a);
                    r->mprod = mapping(f, r->mprod);
                    r->f = composition(f, r->f);
                    r->propagated = false;
                }
                f = id();
                propagated = true;
            }
            if(rev){
                ::std::swap(l, r);
                if(l != NIL) l->rev ^= 1;
                if(r != NIL) r->rev ^= 1;
                rev = 0;
            }
        }
        void prepareUp(){
            mprod = op(op(l->mprod, a), r->mprod);
        }
        MyType*& parentchild(){
            if(p == NIL) return NIL;
            if(p->l == this) return p->l;
            else return p->r;
        }
        void rotL(){
            auto t = p;
            if(t->p != NIL) t->parentchild() = this;
            p = t->p;
            t->p = this;
            if(l != NIL) l->p = t;
            t->r = l;
            l = t;
        }
        void rotR(){
            auto t = p;
            if(t->p != NIL) t->parentchild() = this;
            p = t->p;
            t->p = this;
            if(r != NIL) r->p = t;
            t->l = r;
            r = t;
        }
        void splay(){
            while(p != NIL){
                auto pc = p;
                auto ppc = pc->p;
                if(pc->l == this){
                    if(ppc == NIL){ rotR(); }
                    else if(ppc->l == pc){ pc->rotR(); rotR(); }
                    else if(ppc->r == pc){ rotR(); rotL(); }
                }
                else{
                    if(ppc == NIL){ rotL(); }
                    else if(ppc->r == pc){ pc->rotL(); rotL(); }
                    else if(ppc->l == pc){ rotL(); rotR(); }
                }
                if(ppc != NIL) ppc->prepareUp();
                if(pc != NIL) pc->prepareUp();
            }
            prepareUp();
        }

        std::vector<S> dump(){
            if(this == NIL) return std::vector<S>();
            std::vector<std::pair<bool, MyType*>> dfsStack;
            dfsStack.push_back(std::make_pair(false, this));
            std::vector<S> res;
            while(!dfsStack.empty()){
                auto [f, p] = dfsStack.back();
                dfsStack.pop_back();
                if(f){
                    res.push_back(p->a);
                }
                else{
                    p->prepareDown();
                    if(p->r != NIL) dfsStack.push_back(std::make_pair(false, p->r));
                    dfsStack.push_back(std::make_pair(true, p));
                    if(p->l != NIL) dfsStack.push_back(std::make_pair(false, p->l));
                }
            }
            return res;
        }

        void erase(){
            if(this == NIL) return;
            std::vector<MyType*> dfsStack;
            dfsStack.push_back(this);
            while(!dfsStack.empty()){
                auto p = dfsStack.back();
                dfsStack.pop_back();
                p->prepareDown();
                if(p->r != NIL) dfsStack.push_back(p->r);
                if(p->l != NIL) dfsStack.push_back(p->l);
                delete(p);
            }
        }
        
        static MyType* construct(const std::vector<S>& A){
            struct DFS{
                static MyType* dfs(typename std::vector<S>::const_iterator l, typename std::vector<S>::const_iterator r) {
                    if(l == r) return NIL;
                    int m = std::distance(l, r) / 2;
                    MyType* res = newNode(*(l+m));
                    res->l = dfs(l, l+m);
                    res->r = dfs(l+(m+1), r);
                    if(res->l != NIL) res->l->p = res;
                    if(res->r != NIL) res->r->p = res;
                    res->prepareUp();
                    return res;
                }
            };
            return DFS::dfs(A.begin(), A.end());
        }

        template<class IsTooLarge>
        static std::pair<MyType*, MyType*> splitWhereFalse(MyType*& R, IsTooLarge f){
            if(R == NIL) return std::make_pair(NIL, NIL);
            if(!f(R->mprod)) return std::make_pair(R, NIL);
            if(f(e())) return std::make_pair(NIL, R);
            S leftProd = e();
            MyType* c = R;
            while(true){
                c->prepareDown();
                S tmpProd = op(leftProd, c->l->mprod);
                if(f(tmpProd)){ c = c->l; continue; }
                leftProd = tmpProd;
                tmpProd = op(leftProd, c->a);
                if(f(tmpProd)){ break; }
                leftProd = tmpProd;
                c = c->r;
            }
            c->prepareDown();
            c->splay();
            MyType* b = c->l;
            if(b != NIL){
                b->p = NIL; c->l = NIL; c->prepareUp();
            }
            return std::make_pair(b, c);
        }
        
        template<class IsTooLarge>
        static std::pair<MyType*, MyType*> splitWhereTrue(MyType*& R, IsTooLarge f){
            if(R == NIL) return std::make_pair(NIL, NIL);
            if(!f(R->mprod)) return std::make_pair(R, NIL);
            if(f(e())) return std::make_pair(NIL, R);
            S leftProd = e();
            MyType* c = R;
            while(true){
                c->prepareDown();
                S tmpProd = op(leftProd, c->l->mprod);
                if(f(tmpProd)){ c = c->l; continue; }
                leftProd = tmpProd;
                tmpProd = op(leftProd, c->a);
                if(f(tmpProd)){ break; }
                leftProd = tmpProd;
                c = c->r;
            }
            c->prepareDown();
            c->splay();
            MyType* b = c->r;
            if(b != NIL){
                b->p = NIL; c->r = NIL; c->prepareUp();
            }
            return std::make_pair(c, b);
        }

        static MyType* merge(MyType* l, MyType* r){
            if(l == NIL) return r;
            if(r == NIL) return l;
            r->prepareDown();
            while (r->l != NIL) { r = r->l; r->prepareDown(); }
            r->splay();
            r->prepareDown();
            l->p = r; r->l = l; r->prepareUp();
            return r;
        }
        static void reverse(MyType*& c){
            c->rev ^= 1;
            c->prepareDown();
            c->splay();
        }
        static void apply(MyType*& c, F f){
            c->a = mapping(f,c->a);
            c->mprod = mapping(f,c->mprod);
            c->f = composition(f,c->f);
            c->propagated = false;
            c->prepareDown();
            c->splay();
        }
        static S prod(MyType*& c){
            return c->mprod;
        }

        static MyType* get_NIL(){
            if(NIL) return NIL;
            NIL = new MyType();
            NIL->l = NIL->r = NIL->p = NIL;
            return NIL;
        }

        static MyType* newNode(const S& x){
            MyType* nx = new MyType(*NIL);
            nx->a = nx->mprod = x;
            return nx;
        }
    };

    template<
        class S,
        class F,
        S op(S l, S r),
        S e(),
        void reverseprod(S& x),
        S mapping(F f, S x),
        F composition(F f, F x),
        F id()
    >
        SplayTreeByIdx<S,F,op,e,reverseprod,mapping,composition,id> *
        SplayTreeByIdx<S,F,op,e,reverseprod,mapping,composition,id>
        ::NIL
        = get_NIL();


} // namespace nachia


namespace BST{
    using u32 = unsigned int;
    using u64 = unsigned long long;
    const u32 MOD = 998244353;

    using S = ::F;
    struct F{};
    S op(S l, S r){ return l + r; }
    S e(){ return {1,0,0}; }
    void reverseprod(S&) {}
    S mapping(F , S x){ return x; }
    F composition(F , F x){ return x; }
    F id(){ return {}; }
    using BST = nachia::SplayTreeByIdx<S, F, op, e, reverseprod, mapping, composition, id>;

    struct At {
        u32 i;
        At(u32 at) : i(at) {}
        bool operator()(const S& x){ return i < x.z; }
    };

    void insertAt(BST*& R, int at, S s){
        auto [l,r] = BST::splitWhereFalse(R, At(at));
        R = BST::merge(BST::merge(l, BST::newNode(s)), r);
    }
    void eraseAt(BST*& R, int at){
        auto [l,r] = BST::splitWhereFalse(R, At(at+1));
        auto [ll,lr] = BST::splitWhereFalse(l, At(at));
        delete(lr);
        R = BST::merge(ll, r);
    }
    S prod(BST*& R){
        return R->mprod;
    }
}


#include <cstdio>

int main(){
    int Q; scanf("%d", &Q);

    BST::BST* bst = BST::BST::NIL;
    int size = 0;

    for(int i=0; i<Q; i++){
        int ty; scanf("%d", &ty);
        if(ty == 0){
            u32 a, b; scanf("%d %d", &a, &b);
            BST::insertAt(bst, 0, {a,b,1});
            size++;
        }
        if(ty == 1){
            u32 a, b; scanf("%d %d", &a, &b);
            BST::insertAt(bst, size, {a,b,1});
            size++;
        }
        if(ty == 2){
            BST::eraseAt(bst, 0);
            size--;
        }
        if(ty == 3){
            BST::eraseAt(bst, size-1);
            size--;
        }
        if(ty == 4){
            u32 x; scanf("%d", &x);
            u32 ans = (BST::prod(bst)) (x);
            printf("%u\n", ans);
        }
    }
    return 0;
}
