Реализовать класс строк с отложенным копированием при записи.
Буфер для строки и дополнительные поля должны быть выделены в отдельную структуру
(используйте идиому PIMPL). Интерфейс строки должен быть отделен от реализации.

String c, a = "abc";
String b = a; // в памяти хранится "abc" в одном экземпляре
c = a;
b += "aaa"; // для b создался новый "массив" символов.
c[1] = 'f'; // a не изменилось
cout << string(c);
Для хранения данных не используйте std::string и умные указатели.


#include <string>
#include <vector>
#include <sstream>

class HiddenImpl {
    friend class String;

    HiddenImpl() : use_count(1) {}

    explicit HiddenImpl(const std::string &s) : use_count(1) {
        for (const char &c : s) {
            data.emplace_back(c);
        }
    }

    explicit HiddenImpl(const char *s) : use_count(1) {
        while (*s != '\0') {
            data.emplace_back(*s);
            s++;
        }
    }

    explicit HiddenImpl(std::vector<char> v) : data(std::move(v)), use_count(1) {}

    std::vector<char> data;
    size_t use_count;
};

class String {
public:
    String() : pimpl(new HiddenImpl()) {}

    String(const std::string &s) : pimpl(new HiddenImpl(s)) {}

    String(const char *s) : pimpl(new HiddenImpl(s)) {}

    ~String() {
        decrease_and_maybe_delete_pimpl();
    }

    String(const String &other) : pimpl(other.pimpl) {
        pimpl->use_count++;
    }

    String &operator=(const String &other) {
        if (this != &other) {
            decrease_and_maybe_delete_pimpl();
            pimpl = other.pimpl;
            pimpl->use_count++;
        }
        return *this;
    }

    String &operator+=(const std::string &s) {
        std::vector<char> new_vect;
        for (char &c : pimpl->data) {
            new_vect.emplace_back(c);
        }
        for (const char &c : s) {
            new_vect.emplace_back(c);
        }

        decrease_and_maybe_delete_pimpl();
        pimpl = new HiddenImpl(new_vect);
        return *this;
    }

    explicit operator std::string() const {
        std::stringstream s;
        for (char &c : pimpl->data) {
            s << c;
        }
        return s.str();
    }

    class ProxyChar {
    public:
        explicit ProxyChar(char &s, HiddenImpl **outer_pimpl) : data(s), pointer_to_pimpl(outer_pimpl) {}

        operator char() const {
            return data;
        }

        ProxyChar &operator=(char c) {
            HiddenImpl *old_pimpl = *pointer_to_pimpl;
            if (old_pimpl->use_count == 1) {
                data = c;
                return *this;
            }
            std::vector<char> new_data;
            for (char &character : old_pimpl->data) {
                new_data.emplace_back(character);
            }
            data = c;

            old_pimpl->use_count--;

            std::vector<char> changed_data = std::move(old_pimpl->data);
            old_pimpl->data = std::move(new_data);

            auto new_pimpl = new HiddenImpl(changed_data);
            *pointer_to_pimpl = new_pimpl;
            return *this;
        }

    private:
        char &data;
        HiddenImpl **pointer_to_pimpl;
    };

    ProxyChar operator[](const size_t index) {
        return ProxyChar(pimpl->data[index], &pimpl);
    }

    const char &operator[](const size_t index) const {
        return pimpl->data[index];
    }

private:

    void decrease_and_maybe_delete_pimpl() {
        pimpl->use_count--;
        if (pimpl->use_count == 0) {
            delete pimpl;
        }
    }

    HiddenImpl *pimpl;
};
