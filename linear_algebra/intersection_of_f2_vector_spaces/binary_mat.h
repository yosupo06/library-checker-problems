class BinaryMat {
private:
    std::vector<int> basis_;
public:
    BinaryMat() {}
    void add(int x) {
        x = this->sift(x);
        if (x != 0) {
            this->basis_.push_back(x);
        }
    }
    int sift(int x) const {
        for (int b: this->basis_) {
            x = std::min(x, x ^ b);
            if (x == 0) return 0;
        }
        return x;
    }
    bool is_indep(int x) const {
        return this->sift(x) != 0;
    }
    std::vector<int> basis() const {
        return this->basis_;
    }
};
