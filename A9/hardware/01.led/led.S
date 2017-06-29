.text 
.globl _start
_start:
     
    /*
     * set GPM4_0 as output
     */
    ldr r0, =0x110002E0  // GPM4CON的地址是0x110002E0
    ldr r1, [r0]         // 先读出原值
    bic r1, r1, #0xf     // 清除bit[3:0]
    orr r1, r1, #1       // 设置bit[3:0]为0b0001
    str r1, [r0]         // 写入GPM4CON


    /*
     *  set GPM4_0 as High
     */
    ldr r0, =0x110002E4  // GPM4DAT的地址是0x110002E4
    ldr r1, [r0]         // 读出原值
    bic r1, r1, #1       // 清除bit[0]为0
    str r1, [r0]         // 写入GPM4_0

halt_loop:
    b halt_loop
    
    


    
    