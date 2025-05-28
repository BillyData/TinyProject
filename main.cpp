#include "Matrix.h"
#include "Vector.h"
#include "LinearSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <cassert>

struct Sample {
    std::vector<double> features;
    double target;
};

void shuffleData(std::vector<Sample>& data) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data.begin(), data.end(), g);
}

double computeRMSE(const Vector& predictions, const Vector& groundTruth) {
    assert(predictions.getSize() == groundTruth.getSize());
    double sumSqError = 0.0;
    int n = predictions.getSize();
    for (int i = 0; i < n; ++i) {
        double diff = predictions.getData()[i] - groundTruth.getData()[i];
        sumSqError += diff * diff;
    }
    return std::sqrt(sumSqError / n);
}

int main() {
    std::ifstream file("machine.data");
    if (!file.is_open()) {
        std::cerr << "Failed to open data file.\n";
        return 1;
    }

    std::vector<Sample> dataset;
    std::string line;

    // Parse CSV format: vendor,model,MYCT,MMIN,MMAX,CACH,CHMIN,CHMAX,PRP,ERP
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        Sample sample;

        // Skip vendor and model
        std::getline(ss, field, ',');
        std::getline(ss, field, ',');

        // Read 6 features: MYCT, MMIN, MMAX, CACH, CHMIN, CHMAX
        for (int i = 0; i < 6; ++i) {
            std::getline(ss, field, ',');
            sample.features.push_back(std::stod(field));
        }

        // Read PRP as target
        std::getline(ss, field, ',');
        sample.target = std::stod(field);

        // ERP is ignored
        dataset.push_back(sample);
    }
    file.close();

    std::cout << "Parsed " << dataset.size() << " samples.\n";
    if (dataset.empty()) {
        std::cerr << "No data loaded.\n";
        return 1;
    }

    shuffleData(dataset);
    int total = dataset.size();
    int trainSize = static_cast<int>(0.8 * total);
    int testSize = total - trainSize;

    std::cout << "Training size: " << trainSize << ", Test size: " << testSize << "\n";

    Matrix A_train(trainSize, 6);
    Vector b_train(trainSize);
    Matrix A_test(testSize, 6);
    Vector b_test(testSize);

    for (int i = 0; i < trainSize; ++i) {
        for (int j = 0; j < 6; ++j)
            A_train(i + 1, j + 1) = dataset[i].features[j];
        b_train(i + 1) = dataset[i].target;
    }

    for (int i = 0; i < testSize; ++i) {
        for (int j = 0; j < 6; ++j)
            A_test(i + 1, j + 1) = dataset[i + trainSize].features[j];
        b_test(i + 1) = dataset[i + trainSize].target;
    }

    // ✅ Sanity check
    std::cout << "\n--- First training row ---\n";
    for (int j = 0; j < 6; ++j)
        std::cout << A_train(1, j + 1) << " ";
    std::cout << "\nTarget: " << b_train(1) << "\n";

    // Train model
    LeastSquaresSystem model(&A_train, &b_train);
    Vector x = model.Solve();

    std::cout << "\nModel parameters (x):\n";
    for (int i = 0; i < x.getSize(); ++i)
        std::cout << "x" << i + 1 << " = " << x.getData()[i] << "\n";

    // Predict and evaluate
    Vector predictions = A_test * x;
    double rmse = computeRMSE(predictions, b_test);
    std::cout << "\nTest RMSE: " << rmse << "\n";

    return 0;
}

