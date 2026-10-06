/* =====================================================================
 * asm_mult.S -- hand-written x86-64 assembly matrix multiply
 *
 *      void asm_mult(double *c, const double *a, const double *b,
 *                    unsigned long n);
 *
 * Computes c = a * b for three n x n row-major matrices, i.e. exactly
 * what this C++ loop does:
 *
 *     for (i = 0; i < n; ++i)
 *         for (j = 0; j < n; ++j) {
 *             c[i*n + j] = 0;
 *             for (k = 0; k < n; ++k)
 *                 c[i*n + j] += a[i*n + k] * b[k*n + j];
 *         }
 *
 * Linux x86-64 System V calling convention (how the C++ caller passes
 * the arguments to us -- first four integer/pointer arguments arrive
 * in these registers):
 *
 *      rdi -> c          (1st argument)
 *      rsi -> a          (2nd argument)
 *      rdx -> b          (3rd argument)
 *      rcx -> n          (4th argument)
 *
 * Register plan (only %rbx is callee-saved, so only it gets saved):
 *      rbx = i           row index
 *      r8  = j           column index
 *      r9  = k           summation index
 *      r10 = a + i*n     pointer to row i of a
 *      r11 = c + i*n     pointer to row i of c
 *      rax = scratch     (index arithmetic)
 *      xmm0 = accumulator for one element of c
 *      xmm1 = a[i*n + k]
 *      xmm2 = b[k*n + j]
 * ===================================================================== */

    .text
    .globl  asm_mult
    .type   asm_mult, @function
asm_mult:
    pushq   %rbx                    /* rbx belongs to our caller */

    xorq    %rbx, %rbx              /* i = 0 */

    /* ---- outer loop over the rows of c ---------------------------- */
.Lrow_loop:
    cmpq    %rcx, %rbx              /* compare i with n */
    jae     .Ldone                  /* i >= n (unsigned) -> finished */

    movq    %rbx, %rax
    imulq   %rcx, %rax              /* rax = i * n */
    leaq    (%rsi,%rax,8), %r10     /* r10 = &a[i*n]  (row i of a) */
    leaq    (%rdi,%rax,8), %r11     /* r11 = &c[i*n]  (row i of c) */

    xorq    %r8, %r8                /* j = 0 */

    /* ---- middle loop over the columns of c ------------------------ */
.Lcol_loop:
    cmpq    %rcx, %r8
    jae     .Lrow_next              /* j >= n -> next row */

    xorpd   %xmm0, %xmm0            /* accumulator = 0.0 */
    xorq    %r9, %r9                /* k = 0 */

    /* ---- inner loop: acc += a[i*n+k] * b[k*n+j] -------------------- */
.Lk_loop:
    cmpq    %rcx, %r9
    jae     .Lk_done                /* k >= n -> element finished */

    movsd   (%r10,%r9,8), %xmm1     /* xmm1 = a[i*n + k] */
    movq    %r9, %rax
    imulq   %rcx, %rax              /* rax = k * n */
    leaq    (%rdx,%rax,8), %rax     /* rax = &b[k*n]  (row k of b) */
    movsd   (%rax,%r8,8), %xmm2     /* xmm2 = b[k*n + j] */

    mulsd   %xmm2, %xmm1            /* xmm1 = a[i*n+k] * b[k*n+j] */
    addsd   %xmm1, %xmm0            /* xmm0 += xmm1 */

    incq    %r9
    jmp     .Lk_loop

.Lk_done:
    movsd   %xmm0, (%r11,%r8,8)     /* c[i*n + j] = accumulator */
    incq    %r8
    jmp     .Lcol_loop

.Lrow_next:
    incq    %rbx
    jmp     .Lrow_loop

.Ldone:
    popq    %rbx
    ret
    .size   asm_mult, .-asm_mult

/* Tell the linker this object does not need an executable stack */
    .section .note.GNU-stack,"",@progbits
