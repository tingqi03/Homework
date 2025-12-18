struct Term { int coef, exp; };
class Polynomial {
    Chain<Term> poly;
public:
    Polynomial() {}
    Polynomial(const Polynomial& p) {
        for (auto i = p.poly.Begin(); i != p.poly.End(); ++i)
            poly.InsertBack(*i);
    }
    ~Polynomial() { poly.Clear(); }

    Polynomial& operator=(const Polynomial& p) {
        if (this != &p) {
            poly.Clear();
            for (auto i = p.poly.Begin(); i != p.poly.End(); ++i)
                poly.InsertBack(*i);
        }
        return *this;
    }

    friend istream& operator>>(istream& is, Polynomial& p) {
        int n; is >> n;
        while (n--) {
            Term t; is >> t.coef >> t.exp;
            p.poly.InsertBack(t);
        }
        return is;
    }
    friend ostream& operator<<(ostream& os, const Polynomial& p) {
        bool first = true;
        for (auto i = p.poly.Begin(); i != p.poly.End(); ++i) {
            if (!first && (*i).coef > 0) os << "+";
            os << (*i).coef << "x^" << (*i).exp;
            first = false;
        }
        return os;
    }
    Polynomial operator+(const Polynomial& b) const {
        Polynomial c;
        auto i = poly.Begin(), j = b.poly.Begin();
        while (i != poly.End() && j != b.poly.End()) {
            if ((*i).exp == (*j).exp) {
                int s = (*i).coef + (*j).coef;
                if (s) c.poly.InsertBack({s, (*i).exp});
                ++i; ++j;
            } else if ((*i).exp > (*j).exp) c.poly.InsertBack(*i++);
            else c.poly.InsertBack(*j++);
        }
        while (i != poly.End()) c.poly.InsertBack(*i++);
        while (j != b.poly.End()) c.poly.InsertBack(*j++);
        return c;
    }
      Polynomial operator-(const Polynomial& b) const {
        Polynomial nb;
        for (auto i = b.poly.Begin(); i != b.poly.End(); ++i)
            nb.poly.InsertBack({-(*i).coef, (*i).exp});
        return *this + nb;
    }
       Polynomial operator*(const Polynomial& b) const {
        Polynomial c;
        for (auto i = poly.Begin(); i != poly.End(); ++i)
            for (auto j = b.poly.Begin(); j != b.poly.End(); ++j) {
                Polynomial t;
                t.poly.InsertBack({(*i).coef * (*j).coef,
                                   (*i).exp + (*j).exp});
                c = c + t;
            }
        return c;
    }

    float Evaluate(float x) const {
        float s = 0;
        for (auto i = poly.Begin(); i != poly.End(); ++i)
            s += (*i).coef * pow(x, (*i).exp);
        return s;
    }
};
