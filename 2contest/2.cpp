namespace numbers {
    class complex_stack {
    public:
        explicit complex_stack(size_t size = 2) {
            mas = new complex[size];
            actual_size = size;
            im_size = 0;
        }

        ~complex_stack() {
            for (size_t i = 0; i < im_size; i++) {
                mas[i].~complex();
            }
            delete[] mas;
        }

        complex_stack(const complex_stack &other) noexcept {
            mas = new complex[other.actual_size];
            for (size_t i = 0; i < other.im_size; i++) {
                new(mas + i) complex(other.mas[i]);
            }
            actual_size = other.actual_size;
            im_size = other.im_size;
        }


        complex_stack &operator=(const complex_stack &other) noexcept {
            if (this == &other) {
                return *this;
            } else {
                for (size_t i = 0; i < im_size; i++) {
                    mas[i].~complex();
                }
                delete[] mas;
                mas = new complex[other.actual_size];
                for (size_t i = 0; i < other.im_size; i++) {
                    new(mas + i) complex(other.mas[i]);
                }
                actual_size = other.actual_size;
                im_size = other.im_size;
                return *this;
            }
        }

        size_t size() const {
            return im_size;
        }

        complex operator[](const int a) const {
            return mas[a];
        }


        friend complex_stack operator<<(const complex_stack &st, complex c);

        friend complex_stack operator~(const complex_stack &st);

        friend complex operator+(const complex_stack &st);

    private:

        complex *mas;
        size_t im_size;
        size_t actual_size;
    };

    complex_stack operator<<(const complex_stack &st, const complex c) {
        size_t new_act_size = st.actual_size * 2;
        if (st.actual_size >= st.im_size + 1) {
            new_act_size /= 2;
        }


        complex_stack new_stack(new_act_size);
        for (size_t i = 0; i < st.im_size; i++) {
            new(new_stack.mas + i) complex(st.mas[i]);
            new_stack.im_size++;
        }
        new(new_stack.mas + new_stack.im_size) complex(c);
        new_stack.im_size++;
        return new_stack;
    }

    complex_stack operator~(const complex_stack &st) {
        complex_stack res(st);
        res.im_size--;
        res.mas[res.im_size].~complex();
        return res;
    }

    complex operator+(const complex_stack &st) {

        return st.mas[st.im_size - 1];
    }


}

