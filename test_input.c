const int maxn = 18;
const int mod = 1000000007;
int dp[maxn][maxn][maxn][maxn][maxn][7];
int list[200];

int equal(int a, int b) {
    if (a == b)
        return 1;
    return 0;
}

int dfs(int a, int b, int c, int d, int e, int last){
    if(dp[a][b][c][d][e][last] != -1)
        return dp[a][b][c][d][e][last];
    if(a + b + c + d + e == 0)
        return 1;
    int ans = 0;
    if (a) ans = (ans + (a - equal(last, 2)) * dfs(a - 1, b, c, d, e, 1)) % mod;
    if (b) ans = (ans + (b - equal(last, 3)) * dfs(a + 1, b - 1, c, d, e, 2)) % mod;
    if (c) ans = (ans + (c - equal(last, 4)) * dfs(a, b + 1, c - 1, d, e, 3)) % mod;
    if (d) ans = (ans + (d - equal(last, 5)) * dfs(a, b, c + 1, d - 1, e, 4)) % mod;
    if (e) ans = (ans + e * dfs(a, b, c, d + 1, e - 1, 5)) % mod;
    dp[a][b][c][d][e][last] = ans % mod;
    return dp[a][b][c][d][e][last];
}

int cns[20];
 
int main(){
    int n = getint();
    int i = 0; 
    while (i < maxn) {
        int j = 0;
        while(j < maxn) {
            int k = 0;
            while(k < maxn) {
                int l = 0;
                while (l < maxn) {
                    int m = 0;
                    while (m < maxn) {
                        int h = 0;
                        while (h < 7) {
                            dp[i][j][k][l][m][h] = -1;
                            h = h + 1;
                        }
                        m = m + 1;
                    }
                    l = l + 1;
                }
                k = k + 1;
            }
            j = j + 1;
        }
        i = i + 1;
    }
    
    i = 0;
    while (i < n) {
        list[i] = getint();
        cns[list[i]] = cns[list[i]] + 1;
        i = i + 1;
    }

    int ans = dfs(cns[1], cns[2], cns[3], cns[4], cns[5], 0);

    putint(ans);

    return ans;
}
/*
IR:
.global:
        DEF maxn
        ASSIGN maxn, 18
        DEF mod
        ASSIGN mod, 1000000007
        DEF dp
        DEF list
        DEF cns
        END
@getint:
@getch:
@getarray:
@putint:
@putch:
@putarray:
@putf:
@starttime:
@stoptime:
@equal:
.M1:
        EQ .t6, a, b
        IF .t6 GOTO .M2
        GOTO .M3
.M2:
        ASSIGN .t7, 1
        GOTO .M5
.M3:
        GOTO .M4
.M4:
        ASSIGN .t7, 0
        GOTO .M5
.M5:
        RET .t7
        END
@dfs:
.M6:
        ASSIGN .t8, 0
        MUL .t9, 734832, a
        ADD .t8, .t8, .t9
        MUL .t9, 40824, b
        ADD .t8, .t8, .t9
        MUL .t9, 2268, c
        ADD .t8, .t8, .t9
        MUL .t9, 126, d
        ADD .t8, .t8, .t9
        MUL .t9, 7, e
        ADD .t8, .t8, .t9
        MUL .t9, 1, last
        ADD .t8, .t8, .t9
        IDX .t10, dp, .t8
        NEQ .t11, .t10, -1
        IF .t11 GOTO .M7
        GOTO .M8
.M7:
        ASSIGN .t12, 0
        MUL .t13, 734832, a
        ADD .t12, .t12, .t13
        MUL .t13, 40824, b
        ADD .t12, .t12, .t13
        MUL .t13, 2268, c
        ADD .t12, .t12, .t13
        MUL .t13, 126, d
        ADD .t12, .t12, .t13
        MUL .t13, 7, e
        ADD .t12, .t12, .t13
        MUL .t13, 1, last
        ADD .t12, .t12, .t13
        IDX .t14, dp, .t12
        ASSIGN .t15, .t14
        GOTO .M10
.M8:
        GOTO .M9
.M9:
        ADD .t16, a, b
        ADD .t17, .t16, c
        ADD .t18, .t17, d
        ADD .t19, .t18, e
        EQ .t20, .t19, 0
        IF .t20 GOTO .M11
        GOTO .M12
.M11:
        ASSIGN .t15, 1
        GOTO .M10
.M12:
        GOTO .M13
.M13:
        DEF ans
        ASSIGN ans, 0
        IF a GOTO .M14
        GOTO .M15
.M14:
        PARAM 2
        PARAM last
        CALL .t21, @equal
        SUB .t22, a, .t21
        SUB .t23, a, 1
        PARAM 1
        PARAM e
        PARAM d
        PARAM c
        PARAM b
        PARAM .t23
        CALL .t24, @dfs
        MUL .t25, .t22, .t24
        ADD .t26, ans, .t25
        MOD .t27, .t26, mod
        ASSIGN ans, .t27
        GOTO .M16
.M15:
        GOTO .M16
.M16:
        IF b GOTO .M17
        GOTO .M18
.M17:
        PARAM 3
        PARAM last
        CALL .t28, @equal
        SUB .t29, b, .t28
        ADD .t30, a, 1
        SUB .t31, b, 1
        PARAM 2
        PARAM e
        PARAM d
        PARAM c
        PARAM .t31
        PARAM .t30
        CALL .t32, @dfs
        MUL .t33, .t29, .t32
        ADD .t34, ans, .t33
        MOD .t35, .t34, mod
        ASSIGN ans, .t35
        GOTO .M19
.M18:
        GOTO .M19
.M19:
        IF c GOTO .M20
        GOTO .M21
.M20:
        PARAM 4
        PARAM last
        CALL .t36, @equal
        SUB .t37, c, .t36
        ADD .t38, b, 1
        SUB .t39, c, 1
        PARAM 3
        PARAM e
        PARAM d
        PARAM .t39
        PARAM .t38
        PARAM a
        CALL .t40, @dfs
        MUL .t41, .t37, .t40
        ADD .t42, ans, .t41
        MOD .t43, .t42, mod
        ASSIGN ans, .t43
        GOTO .M22
.M21:
        GOTO .M22
.M22:
        IF d GOTO .M23
        GOTO .M24
.M23:
        PARAM 5
        PARAM last
        CALL .t44, @equal
        SUB .t45, d, .t44
        ADD .t46, c, 1
        SUB .t47, d, 1
        PARAM 4
        PARAM e
        PARAM .t47
        PARAM .t46
        PARAM b
        PARAM a
        CALL .t48, @dfs
        MUL .t49, .t45, .t48
        ADD .t50, ans, .t49
        MOD .t51, .t50, mod
        ASSIGN ans, .t51
        GOTO .M25
.M24:
        GOTO .M25
.M25:
        IF e GOTO .M26
        GOTO .M27
.M26:
        ADD .t52, d, 1
        SUB .t53, e, 1
        PARAM 5
        PARAM .t53
        PARAM .t52
        PARAM c
        PARAM b
        PARAM a
        CALL .t54, @dfs
        MUL .t55, e, .t54
        ADD .t56, ans, .t55
        MOD .t57, .t56, mod
        ASSIGN ans, .t57
        GOTO .M28
.M27:
        GOTO .M28
.M28:
        MOD .t58, ans, mod
        ASSIGN .t59, 0
        MUL .t60, 734832, a
        ADD .t59, .t59, .t60
        MUL .t60, 40824, b
        ADD .t59, .t59, .t60
        MUL .t60, 2268, c
        ADD .t59, .t59, .t60
        MUL .t60, 126, d
        ADD .t59, .t59, .t60
        MUL .t60, 7, e
        ADD .t59, .t59, .t60
        MUL .t60, 1, last
        ADD .t59, .t59, .t60
        IDX .t61, dp, .t59
        ASSIGN .t61, .t58
        ASSIGN .t62, 0
        MUL .t63, 734832, a
        ADD .t62, .t62, .t63
        MUL .t63, 40824, b
        ADD .t62, .t62, .t63
        MUL .t63, 2268, c
        ADD .t62, .t62, .t63
        MUL .t63, 126, d
        ADD .t62, .t62, .t63
        MUL .t63, 7, e
        ADD .t62, .t62, .t63
        MUL .t63, 1, last
        ADD .t62, .t62, .t63
        IDX .t64, dp, .t62
        ASSIGN .t15, .t64
        GOTO .M10
.M10:
        RET .t15
        END
@main:
.M29:
        DEF n
        CALL .t65, @getint
        ASSIGN n, .t65
        DEF i
        ASSIGN i, 0
        GOTO .M30
.M30:
        LT .t66, i, maxn
        IF .t66 GOTO .M31
        GOTO .M32
.M31:
        DEF j
        ASSIGN j, 0
        GOTO .M33
.M33:
        LT .t67, j, maxn
        IF .t67 GOTO .M34
        GOTO .M35
.M34:
        DEF k
        ASSIGN k, 0
        GOTO .M36
.M36:
        LT .t68, k, maxn
        IF .t68 GOTO .M37
        GOTO .M38
.M37:
        DEF l
        ASSIGN l, 0
        GOTO .M39
.M39:
        LT .t69, l, maxn
        IF .t69 GOTO .M40
        GOTO .M41
.M40:
        DEF m
        ASSIGN m, 0
        GOTO .M42
.M42:
        LT .t70, m, maxn
        IF .t70 GOTO .M43
        GOTO .M44
.M43:
        DEF h
        ASSIGN h, 0
        GOTO .M45
.M45:
        LT .t71, h, 7
        IF .t71 GOTO .M46
        GOTO .M47
.M46:
        ASSIGN .t72, 0
        MUL .t73, 734832, i
        ADD .t72, .t72, .t73
        MUL .t73, 40824, j
        ADD .t72, .t72, .t73
        MUL .t73, 2268, k
        ADD .t72, .t72, .t73
        MUL .t73, 126, l
        ADD .t72, .t72, .t73
        MUL .t73, 7, m
        ADD .t72, .t72, .t73
        MUL .t73, 1, h
        ADD .t72, .t72, .t73
        IDX .t74, dp, .t72
        ASSIGN .t74, -1
        ADD .t75, h, 1
        ASSIGN h, .t75
        GOTO .M45
.M47:
        ADD .t76, m, 1
        ASSIGN m, .t76
        GOTO .M42
.M44:
        ADD .t77, l, 1
        ASSIGN l, .t77
        GOTO .M39
.M41:
        ADD .t78, k, 1
        ASSIGN k, .t78
        GOTO .M36
.M38:
        ADD .t79, j, 1
        ASSIGN j, .t79
        GOTO .M33
.M35:
        ADD .t80, i, 1
        ASSIGN i, .t80
        GOTO .M30
.M32:
        ASSIGN i, 0
        GOTO .M48
.M48:
        LT .t81, i, n
        IF .t81 GOTO .M49
        GOTO .M50
.M49:
        CALL .t82, @getint
        ASSIGN .t83, 0
        MUL .t84, 1, i
        ADD .t83, .t83, .t84
        IDX .t85, list, .t83
        ASSIGN .t85, .t82
        ASSIGN .t86, 0
        ASSIGN .t88, 0
        MUL .t89, 1, i
        ADD .t88, .t88, .t89
        IDX .t90, list, .t88
        MUL .t87, 1, .t90
        ADD .t86, .t86, .t87
        IDX .t91, cns, .t86
        ADD .t92, .t91, 1
        ASSIGN .t93, 0
        ASSIGN .t95, 0
        MUL .t96, 1, i
        ADD .t95, .t95, .t96
        IDX .t97, list, .t95
        MUL .t94, 1, .t97
        ADD .t93, .t93, .t94
        IDX .t98, cns, .t93
        ASSIGN .t98, .t92
        ADD .t99, i, 1
        ASSIGN i, .t99
        GOTO .M48
.M50:
        DEF ans
        ASSIGN .t100, 0
        MUL .t101, 1, 1
        ADD .t100, .t100, .t101
        IDX .t102, cns, .t100
        ASSIGN .t103, 0
        MUL .t104, 1, 2
        ADD .t103, .t103, .t104
        IDX .t105, cns, .t103
        ASSIGN .t106, 0
        MUL .t107, 1, 3
        ADD .t106, .t106, .t107
        IDX .t108, cns, .t106
        ASSIGN .t109, 0
        MUL .t110, 1, 4
        ADD .t109, .t109, .t110
        IDX .t111, cns, .t109
        ASSIGN .t112, 0
        MUL .t113, 1, 5
        ADD .t112, .t112, .t113
        IDX .t114, cns, .t112
        PARAM 0
        PARAM .t114
        PARAM .t111
        PARAM .t108
        PARAM .t105
        PARAM .t102
        CALL .t115, @dfs
        ASSIGN ans, .t115
        PARAM ans
        CALL .t116, @putint
        ASSIGN .t117, ans
        GOTO .M51
.M51:
        RET .t117
        END

*/