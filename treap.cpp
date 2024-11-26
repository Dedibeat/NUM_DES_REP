typedef struct item* pitem;
struct item {
    int prior, value, cnt;
    int sum;     // Subtree sum
    bool rev;
    int add;     // Lazy addition
    pitem l, r;
    item(int val) {
        prior = rand();
        value = val;
        cnt = 1;
        sum = val;
        rev = false;
        add = 0;
        l = r = nullptr;
    }
};
int cnt(pitem it) {
    return it ? it->cnt : 0;
}
int sum(pitem it) {
    return it ? it->sum : 0;
}
void push(pitem it) {
    if (!it) return;
    if (it->rev) {
        it->rev = false;
        std::swap(it->l, it->r);
        if (it->l) it->l->rev ^= true;
        if (it->r) it->r->rev ^= true;
    }
    if (it->add) {
        it->value += it->add;
        it->sum += it->add * cnt(it);
        if (it->l) it->l->add += it->add;
        if (it->r) it->r->add += it->add;
        it->add = 0;
    }
}
void upd_cnt(pitem it) {
    if (it) {
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
        it->sum = sum(it->l) + sum(it->r) + it->value;
    }
}
void merge(pitem& t, pitem l, pitem r) {
    push(l);
    push(r);
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior) {
        merge(l->r, l->r, r);
        t = l;
    } else {
        merge(r->l, l, r->l);
        t = r;
    }
    upd_cnt(t);
}
void split(pitem t, pitem& l, pitem& r, int key, int add = 0) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    push(t);
    int cur_key = add + cnt(t->l);
    if (key <= cur_key) {
        split(t->l, l, t->l, key, add);
        r = t;
    } else {
        split(t->r, t->r, r, key, add + 1 + cnt(t->l));
        l = t;
    }
    upd_cnt(t);
}
void insert(pitem& t, pitem it, int pos) {
    if (!t) {
        t = it;
        return;
    }
    push(t);
    int lcnt = cnt(t->l);
    if (it->prior > t->prior) {
        split(t, it->l, it->r, pos);
        t = it;
    } else {
        if (pos <= lcnt)
            insert(t->l, it, pos);
        else
            insert(t->r, it, pos - lcnt - 1);
    }
    upd_cnt(t);
}
void erase(pitem& t, int pos) {
    if (!t) return;
    push(t);
    int lcnt = cnt(t->l);
    if (pos == lcnt) {
        pitem temp = t;
        merge(t, t->l, t->r);
        delete temp;
    } else if (pos < lcnt) {
        erase(t->l, pos);
    } else {
        erase(t->r, pos - lcnt - 1);
    }
    upd_cnt(t);
}
int range_query(pitem& t, int l, int r) {
    pitem t1, t2, t3;
    split(t, t1, t2, l);
    split(t2, t2, t3, r - l + 1);
    int ans = sum(t2);
    merge(t2, t2, t3);
    merge(t, t1, t2);
    return ans;
}
void range_add(pitem& t, int l, int r, int val) {
    pitem t1, t2, t3;
    split(t, t1, t2, l);
    split(t2, t2, t3, r - l + 1);
    if (t2) t2->add += val;
    merge(t2, t2, t3);
    merge(t, t1, t2);
}
int kth(pitem t, int k) {
    if (!t) return -1; // Or some error value
    push(t);
    int lcnt = cnt(t->l);
    if (k < lcnt)
        return kth(t->l, k);
    else if (k == lcnt)
        return t->value;
    else
        return kth(t->r, k - lcnt - 1);
}
void reverse(pitem& t, int l, int r) {
    pitem t1, t2, t3;
    split(t, t1, t2, l);
    split(t2, t2, t3, r - l + 1);
    if (t2) t2->rev ^= true;
    merge(t, t1, t2);
    merge(t, t, t3);
}
void output(pitem t) {
    if (!t) return;
    push(t);
    output(t->l);
    printf("%d ", t->value);
    output(t->r);
}
