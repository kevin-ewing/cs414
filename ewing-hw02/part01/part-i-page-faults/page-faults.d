/* page-faults.d */

fbt:kernel:vm_fault_trap:
/pid == $target/
{
    printf("\t%s arg1: 0x%x", probename, arg1);
}