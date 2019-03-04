class QU {
public:
	QU(int i) {
		id = new int[size = i];
		sz = new int[size];
		for (int i = 0; i < size; ++i) {
			id[i] = i;
			sz[i] = 1;
		}
	}
	~QU() {
		delete[] id;
	}
	int root(const int i)const {
		int j = i;
		while (j != id[j]) 
			j = id[j];
		return j;
	}
	bool connected(const int p, const int q) const {
		return root(p) == root(q);
	}
	void make_union(const int p,const int q){
		int i = root(p);
		int j = root(q);
		if (i == j) return;
		if (sz[i] < sz[j]) { id[i] = j; sz[j] += sz[i];}
		else { id[j] = i; sz[i] += sz[j];}
	}

private:
	int size;
	int* id;
	int* sz;
};
