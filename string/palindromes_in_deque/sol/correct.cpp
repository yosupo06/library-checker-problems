
#include <vector>
#include <algorithm>
#include <iterator>

namespace nachia {

template<class Elem>
struct AmortizedDeque {
private:
    std::vector<Elem> l;
    std::vector<Elem> r;
    static void reset_halfway(std::vector<Elem>& a, std::vector<Elem>& b){
        auto m = (b.size() + 1) / 2;
        std::move(b.rend() - m, b.rend(), std::back_inserter(a));
        b.erase(b.begin(), b.begin() + m);
    }
public:
    void push_back(Elem& x){ r.push_back(x); }
    void push_back(Elem&& x){ r.push_back(std::move(x)); }
    void push_front(Elem& x){ l.push_back(x); }
    void push_front(Elem&& x){ l.push_back(std::move(x)); }
    Elem& operator[](std::size_t i){
        return i < l.size() ? l[l.size() - 1 - i] : r[i - l.size()];
    }
    const Elem& operator[](std::size_t i) const {
        return i < l.size() ? l[l.size() - 1 - i] : r[i - l.size()];
    }
    Elem& at(std::size_t i){
        return i < l.size() ? l.at(l.size() - 1 - i) : r.at(i - l.size());
    }
    const Elem& at(std::size_t i) const {
        return i < l.size() ? l.at(l.size() - 1 - i) : r.at(i - l.size());
    }
    std::size_t size(){ return l.size() + r.size(); }
    void pop_back(){
        if(r.empty()) reset_halfway(r, l);
        r.pop_back();
    }
    void pop_front(){
        if(l.empty()) reset_halfway(l, r);
        l.pop_back();
    }
    Elem& back(){ return r.empty() ? l.front() : r.back(); }
    const Elem& back() const { return r.empty() ? l.front() : r.back(); }
    Elem& front(){ return l.empty() ? r.front() : l.back(); }
    const Elem& front() const { return l.empty() ? r.front() : l.back(); }
    bool empty() const { return l.empty() && r.empty(); }
};

} // namespace nachia

#include <memory>
#include <map>


namespace nachia{

using Char = int;
using NextDs = std::map<Char, struct Node*>;
struct Node {
    Node* parent;
    Node* link;
    Node* quick;
    NextDs next;
    int len = 0;
    int cnt = 0;
    int linkcnt = 0;
};
struct DequeNode {
    Char ch;
    Node* presurf;
    Node* sufsurf;
};

struct DequePalindromicTree {
private:
    AmortizedDeque<DequeNode> deq;
    std::unique_ptr<Node> Odd;
    std::unique_ptr<Node> Even;
    int numNodes;
    
    Node* backAppendable(Char c, Node* p){
        auto n = int(deq.size());
        while(true){
            if(p->len == -1 || (p->len < n && deq[n - p->len - 1].ch == c)) return p;
            auto q = p->link;
            if(q->len == -1 || deq[n - q->len - 1].ch == c) return q;
            p = p->quick;
        }
    }
    Node* frontAppendable(Char c, Node* p){
        auto n = int(deq.size());
        while(true){
            if(p->len == -1 || (p->len < n && deq[p->len].ch == c)) return p;
            auto q = p->link;
            if(q->len == -1 || deq[q->len].ch == c) return q;
            p = p->quick;
        }
    }
public:

    DequePalindromicTree(){
        Odd = std::make_unique<Node>();
        Odd->len = -1;
        Odd->parent = Odd->quick = Odd->link = Odd.get();
        Even = std::make_unique<Node>(*Odd);
        Even->len = 0;
        numNodes = 0;
    }

    ~DequePalindromicTree(){
        while(deq.size()) popBack();
    }

    void pushBack(Char ch){
        auto par = deq.empty() ? Odd.get() : backAppendable(ch, deq.back().sufsurf);
        auto n = int(deq.size());
        Node* v = nullptr;
        Node* w = Even.get();
        auto vit = par->next.find(ch);
        if(vit == par->next.end()){
            v = new Node();
            v->cnt = 0;
            v->linkcnt = 0;
            v->parent = par;
            v->len = par->len + 2;
            if(par != Odd.get()) w = backAppendable(ch, par->link)->next[ch];
            v->link = w;
            w->linkcnt += 1;
            deq.push_back(DequeNode{ ch, Even.get(), Even.get() });
            n += 1;
            if(w->link != Odd.get() && deq[n - w->len - 1].ch == deq[n - w->link->len - 1].ch){
                v->quick = w->quick;
            } else {
                v->quick = w->link;
            }
            par->next.insert(std::make_pair(ch, v));
            numNodes += 1;
        } else {
            deq.push_back(DequeNode{ ch, Even.get(), Even.get() });
            n += 1;
            v = vit->second;
            w = v->link;
        }
        deq[n-1].sufsurf = v;
        deq[n-v->len].presurf = v;
        if(w->len >= 1 && deq[n - v->len + w->len - 1].sufsurf == w){
            deq[n - v->len + w->len - 1].sufsurf = Even.get();
        }
        v->cnt += 1;
    }

    void pushFront(Char ch){
        auto par = deq.empty() ? Odd.get() : frontAppendable(ch, deq.front().presurf);
        // auto n = int(deq.size());
        Node* v = nullptr;
        Node* w = Even.get();
        auto vit = par->next.find(ch);
        if(vit == par->next.end()){
            v = new Node();
            v->cnt = 0;
            v->linkcnt = 0;
            v->parent = par;
            v->len = par->len + 2;
            if(par != Odd.get()) w = frontAppendable(ch, par->link)->next[ch];
            v->link = w;
            w->linkcnt += 1;
            deq.push_front(DequeNode{ ch, Even.get(), Even.get() });
            // n += 1;
            if(w->link != Odd.get() && deq[w->len].ch == deq[w->link->len].ch){
                v->quick = w->quick;
            } else {
                v->quick = w->link;
            }
            par->next.insert(std::make_pair(ch, v));
            numNodes += 1;
        } else {
            deq.push_front(DequeNode{ ch, Even.get(), Even.get() });
            // n += 1;
            v = vit->second;
            w = v->link;
        }
        deq[0].presurf = v;
        deq[v->len - 1].sufsurf = v;
        if(w->len >= 1 && deq[v->len - w->len].presurf == w){
            deq[v->len - w->len].presurf = Even.get();
        }
        v->cnt += 1;
    }

    void popBack(){
        auto v = deq.back().sufsurf;
        int backChar = deq.back().ch;
        auto w = v->link;
        if(v->len >= 2 && deq[deq.size() - v->len + w->len - 1].sufsurf->len < w->len){
            deq[deq.size() - v->len + w->len - 1].sufsurf = w;
            deq[deq.size() - v->len].presurf = w;
        } else {
            deq[deq.size() - v->len].presurf = Even.get();
        }
        v->cnt -= 1;
        if(v->linkcnt == 0 && v->cnt == 0){
            v->parent->next.erase(backChar);
            w->linkcnt -= 1;
            delete v;
            numNodes -= 1;
        }
        deq.pop_back();
    }

    void popFront(){
        auto v = deq.front().presurf;
        int backChar = deq.front().ch;
        auto w = v->link;
        if(v->len >= 2 && deq[v->len - w->len].presurf->len < w->len){
            deq[v->len - w->len].presurf = w;
            deq[v->len - 1].sufsurf = w;
        } else {
            deq[v->len - 1].sufsurf = Even.get();
        }
        v->cnt -= 1;
        if(v->linkcnt == 0 && v->cnt == 0){
            v->parent->next.erase(backChar);
            w->linkcnt -= 1;
            delete v;
            numNodes -= 1;
        }
        deq.pop_front();
    }

    int stringLength(){ return int(deq.size()); }

    int numDistinctPalindromes(){ return numNodes; }
    int longestSuffixPalindrome(){ return stringLength() == 0 ? 0 : deq.back().sufsurf->len; }
    int longestPrefixPalindrome(){ return stringLength() == 0 ? 0 : deq.front().presurf->len; }
};

} // namespace nachia

#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

int main(){
    using namespace std;
    int Q; scanf("%d", &Q);
    auto deq = nachia::DequePalindromicTree();
    for(int qi=0; qi<Q; qi++){
        int t; scanf("%d", &t);
        if(t == 0){
            char c; scanf(" %c", &c);
            deq.pushBack(c);
        }
        else if(t == 1){
            char c; scanf(" %c", &c);
            deq.pushFront(c);
        }
        else if(t == 2){
            deq.popBack();
        }
        else if(t == 3){
            deq.popFront();
        }
        printf("%d %d %d\n",
            deq.numDistinctPalindromes(),
            deq.longestPrefixPalindrome(),
            deq.longestSuffixPalindrome());
    }
    return 0;
}
