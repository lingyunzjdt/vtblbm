#include <benchmark/benchmark.h>

class Base {
public:
    explicit Base(int nx, int ny, int nz) : nx_(nx), ny_(ny), nz_(nz) {
        px = new double[nx_*ny_*nz_];
    }

    ~Base() { delete [] px;}

    virtual void mod(double cord[3], int idx[3]) {
        px[idx[0]*ny_*nz_ + idx[1]*nz_ + idx[2]] = 0.0;
    };

    void trans() {
        double cord[3];
        int idx[3];
        for (int i = 0; i < nx_; ++i) {
            idx[0] = i;
            for (int j = 0; j < ny_; ++j) {
                idx[1] = j;
                for (int k = 0; k < nz_; ++k) {
                    idx[2] = k;
                    mod(cord, idx);
                }
            }
        }
    };

protected:
    double *px;
    int nx_, ny_, nz_;
};

class Deriv : public Base {
public:
    explicit Deriv(int nx, int ny, int nz) : Base(nx, ny, nz) {}
    void mod(double cord[3], int idx[3]) override {
        px[idx[0]*ny_*nz_ + idx[1]*nz_ + idx[2]] = 1.0;
    };

    void trans2() {
        for (int i = 0; i < nx_; ++i) {
            for (int j = 0; j < ny_; ++j) {
                for (int k = 0; k < nz_; ++k) {
                    px[i*ny_*nz_ + j*nz_ + k] = 1.0;
                }
            }
        }
    }
};

static void BM_Deriv(benchmark::State& state) {
    Deriv d(4,5,6);
    double cord[3];
    int idx[3];
    for (auto _ : state) {
        d.trans();
    }
}
// Register the function as a benchmark
BENCHMARK(BM_Deriv);

static void BM_Deriv2(benchmark::State& state) {
    Deriv d(4,5,6);
    for (auto _ : state) {
        d.trans2();
    }
}
// Register the function as a benchmark
BENCHMARK(BM_Deriv2);

BENCHMARK_MAIN();

