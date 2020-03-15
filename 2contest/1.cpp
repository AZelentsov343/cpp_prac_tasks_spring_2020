#include <sstream>
#include <string>
#include <cmath>


namespace numbers {
    class complex {
    public:
        complex(double re = 0, double im = 0) {
            this->real = re;
            this->imaginary = im;
        }

        explicit complex(const std::string& s) {
            const char *str = s.c_str();
            sscanf(str, "(%lf,%lf)", &real, &imaginary);
        }

        double re() const {
            return real;
        }

        double im() const {
            return imaginary;
        }

        double abs2() const {
            return real * real + imaginary * imaginary;
        }

        double abs() const {
            return sqrt(abs2());
        }

        std::string to_string() const {
            std::stringstream stream;
            stream.precision(10);
            stream << '(' << real << ',' << imaginary << ')';
            std::string result = stream.str();
            return result;
        }

        complex operator+=(const complex& other) {
            real += other.re();
            imaginary += other.im();
            return *this;
        }

        complex operator-=(const complex& other) {
            real -= other.re();
            imaginary -= other.im();
            return *this;
        }

        complex operator*=(const complex& other) {
            double new_re = real;
            real = real * other.re() - imaginary * other.im();
            imaginary = new_re * other.im() + imaginary * other.re();
            return *this;
        }

        complex operator/=(const complex& other) {
            *this *= ~other;
            auto div = other.abs2();
            real /= div;
            imaginary /= div;
            return *this;
        }


        complex operator~() const {
            complex c(real, -imaginary);
            return c;
        }

        complex operator-() const {
            complex c(-real, -imaginary);
            return c;
        }

        friend complex operator+(const complex& z1, const complex& z2);
        friend complex operator-(const complex& z1, const complex& z2);
        friend complex operator/(const complex& z1, const complex& z2);
        friend complex operator*(const complex& z1, const complex& z2);


    private:
        double real;
        double imaginary;
    };


    complex operator+(const complex& z1, const complex& z2) {
        complex c(z1.real, z1.imaginary);
        return (c += z2);
    }

    complex operator-(const complex& z1, const complex& z2){
        complex c(z1.real, z1.imaginary);
        return (c -= z2);
    }

    complex operator*(const complex& z1, const complex& z2) {
        complex c(z1.real, z1.imaginary);
        return (c *= z2);
    }

    complex operator/(const complex& z1, const complex& z2) {
        complex c(z1.real, z1.imaginary);
        return (c /= z2);
    }


}
