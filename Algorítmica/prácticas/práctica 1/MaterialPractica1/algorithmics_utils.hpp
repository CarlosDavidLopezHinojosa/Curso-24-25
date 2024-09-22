
#ifndef ALGORITHMICS_UTILS_HPP
#define ALGORITHMICS_UTILS_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <functional>
#include <cassert>
#include <Eigen/Dense>
#include "ClaseTiempo.hpp"


/**
 * Brief explanation:
 * T: represent the data type I want the matrices and vector to be, when ramdon generated
 * R: Is the return type in the algorithm function
 * Args...: In an special multiargument template for functions
 */

/**
 * @brief base class to compute Big O complexity of various kind of algorithms
**/
template <class T, typename Func>
class OComplexity
{
public:
OComplexity(Func algorithm);
~OComplexity() = default;

/**
 * @brief Using Lineal or no Lineal regresion techniques, 
 * finds the corresponding complexity function associated to an algorithm
 */
virtual void calculate_complexity(int max_size, int min_size, int iterations) = 0;

/**
 * @brief After finding the polynomial, estimates the time an algorithm will last given the size of any problem
 * @arg the size of problem
 * @pre is_executed
 */
virtual uint64_t estimation (int n) = 0;

/**
 * @pre is_executed
 * @brief After executing the corresponding iterations, 
 * updates the median, variance, standart deviation and coeficient of determinance
 */
virtual void calculate_statistics() = 0;



double calculated_median() const;
double calculated_variance() const;
double calculated_std_dev() const;
double real_median() const;
double real_variance() const;
double real_std_dev() const;
double determinance() const;

bool is_executed() const;
void set_executed(bool state);

void load_datafile(std::string file_name);
protected:
Func algorithm_;

std::vector<int> sizes;
std::vector<uint64_t> times;

double median_[2];
double variance_[2];
bool is_executed_;

void set_sizes(int tam) { sizes.resize(tam); }
void set_times(int tam) { times.resize(tam); }

int& size_at(size_t i) { return sizes[i]; }
uint64_t& time_at(size_t i) { return times[i]; }

void set_real_median(double median) { median_[0] = median; };
void set_calculated_median(double median) { median_[1] = median; };
void set_real_variance(double variance) { variance_[0] = variance; };
void set_calculated_variance(double variance) { variance_[1] = variance; };

Func apply() const { return algorithm_; }

std::vector<std::vector<T>> generate_random_matrix(int rows, int cols, T max, T min);
};




template <class T, typename Func>
class QuadraticComplexity : public OComplexity<T,Func>
{
public:
QuadraticComplexity(std::function<void(std::vector<T>&)> algorithm) : OComplexity<T,Func>(algorithm) { coeficients_.resize(3); }
void calculate_complexity(int max_size, int min_size, int iterations) override; 
uint64_t estimation(int n) override;
void calculate_statistics() override;


protected:
std::vector<double> coeficients_;
double& coeficient(size_t i) { return coeficients_.at(i); }
std::vector<T> generate_random_vector(int tam, T max, T min);
};

#include "algorithmics_utils_impl.hpp"
#endif