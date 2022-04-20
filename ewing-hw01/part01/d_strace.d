/* d_strace.d */

syscall:::entry
/pid == $target/
{
    printf("\n%s (0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x)", probefunc, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}

syscall:::return
/pid == $target/
{
    printf("\n%s = (0x%x)", probefunc, arg1);
}