#ifndef ALGORITHMICS_UTILS_HPP
#define ALGORITHMICS_UTILS_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <functional>
#include <tuple>
#include <cassert>
#include <Eigen/Dense>
#include "ClaseTiempo.hpp"

/**
 * @brief base class to compute Big O complexity of various kind of algorithms
**/
template <class R, typename... Args>
class PolynomialComplexity
{
public:
    PolynomialComplexity(std::function<R(Args&...)> algorithm, std::function<std::tuple<Args&...>(int)> rand_gen, int degree);
    ~PolynomialComplexity() = default;

    virtual void calculate_complexity(int min_size, int max_size, int iterations);
    virtual uint64_t estimation (int n);
    virtual void calculate_statistics();

    size_t polynomial_degree() const { return coeficients_.size() - 1; }

    // Returns the calculated mean
    double calculated_mean() const;
    double calculated_variance() const;
    double calculated_std_dev() const;

    // Returns the real statistics
    double real_mean() const;
    double real_variance() const;
    double real_std_dev() const;

    // Returns the determination coefficient
    double determinance() const;

    // Checks if execution has completed
    bool is_executed() const;
    void set_executed(bool state);

    // Loads the data from a file
    void load_datafile(const std::string& file_name);

protected:
    std::function<R(Args&...)> algorithm_;
    std::function<std::tuple<Args&...>(int)> rand_gen_;

    std::vector<int> sizes;
    std::vector<uint64_t> times;
    std::vector<double> coeficients_;

    double mean_[2];
    double variance_[2];
    bool is_executed_;

    double& coeficient(size_t i) { return coeficients_.at(i); }
    void set_sizes(int tam) { sizes.resize(tam); }
    void set_times(int tam) { times.resize(tam); }
    int& size_at(size_t i) { return sizes.at(i); }
    uint64_t& time_at(size_t i) { return times.at(i); }

    void set_real_mean(double mean) { mean_[0] = mean; }
    void set_calculated_mean(double mean) { mean_[1] = mean; }
    void set_real_variance(double variance) { variance_[0] = variance; }
    void set_calculated_variance(double variance) { variance_[1] = variance; }

    // Executes the algorithm
    void apply(std::tuple<Args&...> arguments) const { std::apply(algorithm_,arguments); }

    // Generates random data for Args...
    std::tuple<Args&...> generate(int size) const { return rand_gen_(size); }
};



// template <class R, typename... Args>
// class FactorialComplexity : public PolynomialComplexity<R, Args...>
// {
// public:
//     FactorialComplexity(std::function<R(Args...)> algorithm, std::function<std::tuple<Args...>(int)> rand_gen) 
//         : PolynomialComplexity<R, Args...>(algorithm, rand_gen, 1) {  }

//     void calculate_complexity(int min_size, int max_size, int iterations) override;
//     uint64_t estimation(int n) override;
// };
#include "algorithmics_utils_impl.hpp"
#endif
