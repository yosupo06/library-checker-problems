std::vector<int> intersection(const std::vector<int> &u, const std::vector<int> &v) {
    BinaryMat mat;
    for (int x: u) {
        mat.add(x);
    }
    std::vector<std::pair<int, int>> basis;
    BinaryMat intersection;
    for (int x: v) {
        int y = mat.sift(x);
        int u_part = y ^ x;
        int y_sifted = y;
        for (auto v: basis) {
            int tmp = y_sifted ^ v.second;
            if (tmp < y_sifted) {
                y_sifted = tmp;
                u_part ^= v.first;
            }
        }
        if (y_sifted != 0) {
            basis.push_back(std::make_pair(u_part, y_sifted));
        } else {
            intersection.add(u_part);
        }
    }
    return intersection.basis();
}
