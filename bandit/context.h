#ifndef BANDIT_CONTEXT_H
#define BANDIT_CONTEXT_H

namespace bandit {
  namespace detail {

    using namespace std;

    class context
    {
      public:
        virtual void register_before_each(voidfunc_t func) = 0;
        virtual void register_after_each(voidfunc_t func) = 0;
        virtual void run_before_eaches() = 0;
        virtual void run_after_eaches() = 0;
    };

    class bandit_context : public context
    {
      public:
        void register_before_each(voidfunc_t func)
        {
          before_eaches_.push_back(func);
        }

        void register_after_each(voidfunc_t func)
        {
          after_eaches_.push_back(func);
        }

        void run_before_eaches()
        {
          run_all(before_eaches_);
        }

        void run_after_eaches()
        {
          run_all(after_eaches_);
        }

      private:
        void run_all(const list<voidfunc_t>& funcs)
        {
          auto call_func = [](voidfunc_t f){ f(); };

          for_each(funcs.begin(), funcs.end(), call_func);
        }

      private:
        list<voidfunc_t> before_eaches_;
        list<voidfunc_t> after_eaches_;
    };
    typedef deque<context*> contextstack_t;

    inline contextstack_t& context_stack()
    {
      static contextstack_t contexts;
      return contexts;
    }
  }
}

#endif
