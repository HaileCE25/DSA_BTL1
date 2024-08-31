#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
void train_test_split(Dataset &X, Dataset &Y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &Y_train, Dataset &Y_test)
{
    if (X.getData()->length() != Y.getData()->length() || test_size >= 1 || test_size <= 0)
        return;

    int num_train_samples = (int)(X.getData()->length() * (1 - test_size));
    // Chia tập dữ liệu thành tập huấn luyện và kiểm tra
    X_train = X.extract(0, num_train_samples - 1, 0, -1);
    Y_train = Y.extract(0, num_train_samples - 1, 0, -1);

    X_test = X.extract(num_train_samples, -1, 0, -1);
    Y_test = Y.extract(num_train_samples, -1, 0, -1);
}