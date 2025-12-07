const long long mod = 1e18 - 11;

struct BIG_MOD
{
    long long val;
    inline BIG_MOD(long long inp = 0)
    {
        val = inp;
    }
    inline void operator=(const BIG_MOD inp)
    {
        val = inp.val;
    }
    inline BIG_MOD operator+(const BIG_MOD inp)
    {
        return BIG_MOD((val + inp.val) % mod);
    }
    inline BIG_MOD operator-(const BIG_MOD inp)
    {
        return BIG_MOD((val - inp.val + mod) % mod);
    }
    inline BIG_MOD operator*(BIG_MOD inp)
    {
        long long base = val % mod, res = 0;
        do
        {
            (res += ((inp.val % 10) * base) % mod) %= mod;
            (base *= 10LL) %= mod;
        } while (inp.val /= 10);
        return BIG_MOD(res);
    }
    inline BIG_MOD operator^(long long inp)
    {
        BIG_MOD base = (*this), res(1);
        do
        {
            if (inp & 1)
            {
                res = res * base;
            }
            base = base * base;
        } while (inp >>= 1);
        return res;
    }
    inline BIG_MOD operator/(BIG_MOD inp)
    {
        return (*this) * (inp^(mod - 2));
    }
};
