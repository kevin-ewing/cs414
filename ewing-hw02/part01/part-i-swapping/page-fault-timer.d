/* page-faults.d */

fbt:kernel:vm_fault_trap:entry
/pid == $target/
{
    self->ts = timestamp;
}

fbt:kernel:vm_fault_trap:return
/pid == $target/
{
    @ = quantize(timestamp - self->ts);

    self->ts = 0;
}