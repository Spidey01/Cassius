/** convenience function for calling a scripts function with the supplied arguments */
        template <typename Arg1_t, typename Arg2_t, typename Arg3_t, typename Arg4_t, typename Arg5_t, typename Arg6_t, typename Arg7_t, typename Arg8_t> ValueList Call(const char *func, int nrets, Arg1_t arg1, Arg2_t arg2, Arg3_t arg3, Arg4_t arg4, Arg5_t arg5, Arg6_t arg6, Arg7_t arg7, Arg8_t arg8)
        {
            PushFunction(func,  nrets, 8);
            Push(arg1);
            Push(arg2);
            Push(arg3);
            Push(arg4);
            Push(arg5);
            Push(arg6);
            Push(arg7);
            Push(arg8);
            return Call();
        }
        template <typename Arg1_t, typename Arg2_t, typename Arg3_t, typename Arg4_t, typename Arg5_t, typename Arg6_t, typename Arg7_t> ValueList Call(const char *func, int nrets, Arg1_t arg1, Arg2_t arg2, Arg3_t arg3, Arg4_t arg4, Arg5_t arg5, Arg6_t arg6, Arg7_t arg7)
        {
            PushFunction(func,  nrets, 7);
            Push(arg1);
            Push(arg2);
            Push(arg3);
            Push(arg4);
            Push(arg5);
            Push(arg6);
            Push(arg7);
            return Call();
        }
        template <typename Arg1_t, typename Arg2_t, typename Arg3_t, typename Arg4_t, typename Arg5_t, typename Arg6_t> ValueList Call(const char *func, int nrets, Arg1_t arg1, Arg2_t arg2, Arg3_t arg3, Arg4_t arg4, Arg5_t arg5, Arg6_t arg6)
        {
            PushFunction(func,  nrets, 6);
            Push(arg1);
            Push(arg2);
            Push(arg3);
            Push(arg4);
            Push(arg5);
            Push(arg6);
            return Call();
        }
        template <typename Arg1_t, typename Arg2_t, typename Arg3_t, typename Arg4_t, typename Arg5_t> ValueList Call(const char *func, int nrets, Arg1_t arg1, Arg2_t arg2, Arg3_t arg3, Arg4_t arg4, Arg5_t arg5)
        {
            PushFunction(func,  nrets, 5);
            Push(arg1);
            Push(arg2);
            Push(arg3);
            Push(arg4);
            Push(arg5);
            return Call();
        }
        template <typename Arg1_t, typename Arg2_t, typename Arg3_t, typename Arg4_t> ValueList Call(const char *func, int nrets, Arg1_t arg1, Arg2_t arg2, Arg3_t arg3, Arg4_t arg4)
        {
            PushFunction(func,  nrets, 4);
            Push(arg1);
            Push(arg2);
            Push(arg3);
            Push(arg4);
            return Call();
        }
        template <typename Arg1_t, typename Arg2_t, typename Arg3_t> ValueList Call(const char *func, int nrets, Arg1_t arg1, Arg2_t arg2, Arg3_t arg3)
        {
            PushFunction(func,  nrets, 3);
            Push(arg1);
            Push(arg2);
            Push(arg3);
            return Call();
        }
        template <typename Arg1_t, typename Arg2_t> ValueList Call(const char *func, int nrets, Arg1_t arg1, Arg2_t arg2)
        {
            PushFunction(func,  nrets, 2);
            Push(arg1);
            Push(arg2);
            return Call();
        }
        template <typename Arg1_t> ValueList Call(const char *func, int nrets, Arg1_t arg1)
        {
            PushFunction(func,  nrets, 1);
            Push(arg1);
            return Call();
        }

