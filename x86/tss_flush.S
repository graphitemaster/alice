/* The index for TSS structure with two bottoms bit set for a RPL of 3. */
.set SELECTOR, 0x2B

.global tss_flush
tss_flush:
    mov $SELECTOR,  %ax
    ltr %ax
    ret
