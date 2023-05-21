// int t = 0;
// int s[2];
// int add(int x, int y) {
//     return x+y;
// }

// int indexArr(int a[], int i) {
//     if(i>1)return a[i-1];
//     return a[i+1];
// }

// int main(){
//     int c = 0xFF;
//     const int pi = 3;
//     int a = 0;
//     // int a[2][3][4]={1,2, 6, 5};
//     /*   haha*/
//     if(a>5 && pi){
//         a+1;
//         return -1;
//     }
//     ;
//     while(c < 5){
//     c = add(c, 1);
//     }
//     // int x = add(0, index(a[0][1], 2));
//     // print(a);
//     return 0;
// }
// int main(){
//     int a=10;
//     while(a>0){
//         if(a>5){
//             a=a-1;
//             continue;
//         }
//         return a;
//     }
//     return a;
// }
// test if-else-if
int n;
int QuickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int i;
        i = low;
        int j;
        j = high;
        int k;
        k = arr[low];
        while (i < j)
        {
            while(i < j && arr[j] > k - 1)
            {
                j = j - 1;
            }
 
            if(i < j)
            {
                arr[i] = arr[j];
                i = i + 1;
            }
 
            while(i < j && arr[i] < k)
            {
                i = i + 1;
            }
 
            if(i < j)
            {
                arr[j] = arr[i];
                j = j - 1;
            }
        }
 
        arr[i] = k;
        int tmp;
        tmp = i - 1;
        tmp = QuickSort(arr, low, tmp);
        tmp = i + 1;
        tmp = QuickSort(arr, tmp, high);
    }
    return 0;
}

int main(){
    n = 4;
    int a[10];
    a[0]=4;a[1]=3;a[2]=9;a[3]=2;a[4]=0;
    a[5]=1;a[6]=6;a[7]=5;a[8]=7;a[9]=8;
    int i;
    i = 0;
    int tmp;
    tmp = 3;
    i = QuickSort(a, i, tmp);
    while (i < n) {
        int tmp;
        tmp = a[i];
        putint(tmp);
        tmp = 10;
        putch(tmp);
        i = i + 1;
    }
    return 0;
}
/*
IR:
.global:
        DEF n
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
@QuickSort:
.M1:
        LT .t6, low, high
        IF .t6 GOTO .M2
        GOTO .M3
.M2:
        DEF i
        ASSIGN i, low
        DEF j
        ASSIGN j, high
        DEF k
        ASSIGN .t7, 0
        MUL .t8, 1, low
        ADD .t7, .t7, .t8
        IDX .t9, arr, .t7
        ASSIGN k, .t9
        GOTO .M5
.M5:
        LT .t10, i, j
        IF .t10 GOTO .M6
        GOTO .M7
.M6:
        GOTO .M8
.M8:
        LT .t11, i, j
        IF .t11 GOTO .M11
        GOTO .M10
.M11:
        ASSIGN .t12, 0
        MUL .t13, 1, j
        ADD .t12, .t12, .t13
        IDX .t14, arr, .t12
        SUB .t15, k, 1
        GT .t16, .t14, .t15
        IF .t16 GOTO .M9
        GOTO .M10
.M9:
        SUB .t17, j, 1
        ASSIGN j, .t17
        GOTO .M8
.M10:
        LT .t18, i, j
        IF .t18 GOTO .M12
        GOTO .M13
.M12:
        ASSIGN .t19, 0
        MUL .t20, 1, j
        ADD .t19, .t19, .t20
        IDX .t21, arr, .t19
        ASSIGN .t22, 0
        MUL .t23, 1, i
        ADD .t22, .t22, .t23
        IDX .t24, arr, .t22
        ASSIGN .t24, .t21
        ADD .t25, i, 1
        ASSIGN i, .t25
        GOTO .M14
.M13:
        GOTO .M14
.M14:
        GOTO .M15
.M15:
        LT .t26, i, j
        IF .t26 GOTO .M18
        GOTO .M17
.M18:
        ASSIGN .t27, 0
        MUL .t28, 1, i
        ADD .t27, .t27, .t28
        IDX .t29, arr, .t27
        LT .t30, .t29, k
        IF .t30 GOTO .M16
        GOTO .M17
.M16:
        ADD .t31, i, 1
        ASSIGN i, .t31
        GOTO .M15
.M17:
        LT .t32, i, j
        IF .t32 GOTO .M19
        GOTO .M20
.M19:
        ASSIGN .t33, 0
        MUL .t34, 1, i
        ADD .t33, .t33, .t34
        IDX .t35, arr, .t33
        ASSIGN .t36, 0
        MUL .t37, 1, j
        ADD .t36, .t36, .t37
        IDX .t38, arr, .t36
        ASSIGN .t38, .t35
        SUB .t39, j, 1
        ASSIGN j, .t39
        GOTO .M21
.M20:
        GOTO .M21
.M21:
        GOTO .M5
.M7:
        ASSIGN .t40, 0
        MUL .t41, 1, i
        ADD .t40, .t40, .t41
        IDX .t42, arr, .t40
        ASSIGN .t42, k
        DEF tmp
        SUB .t43, i, 1
        ASSIGN tmp, .t43
        ASSIGN .t44, 0
        IDX .t46, arr, .t44
        ARR , .t46
        PARAM tmp
        PARAM low
        PARAM 
        CALL .t48, @QuickSort
        ASSIGN tmp, .t48
        ADD .t49, i, 1
        ASSIGN tmp, .t49
        ASSIGN .t50, 0
        IDX .t52, arr, .t50
        ARR , .t52
        PARAM high
        PARAM tmp
        PARAM 
        CALL .t54, @QuickSort
        ASSIGN tmp, .t54
        GOTO .M4
.M3:
        GOTO .M4
.M4:
        ASSIGN .t55, 0
        GOTO .M22
.M22:
        RET .t55
        END
@main:
.M23:
        ASSIGN n, 10
        DEF a
        ASSIGN .t56, 0
        MUL .t57, 1, 0
        ADD .t56, .t56, .t57
        IDX .t58, a, .t56
        ASSIGN .t58, 4
        ASSIGN .t59, 0
        MUL .t60, 1, 1
        ADD .t59, .t59, .t60
        IDX .t61, a, .t59
        ASSIGN .t61, 3
        ASSIGN .t62, 0
        MUL .t63, 1, 2
        ADD .t62, .t62, .t63
        IDX .t64, a, .t62
        ASSIGN .t64, 9
        ASSIGN .t65, 0
        MUL .t66, 1, 3
        ADD .t65, .t65, .t66
        IDX .t67, a, .t65
        ASSIGN .t67, 2
        ASSIGN .t68, 0
        MUL .t69, 1, 4
        ADD .t68, .t68, .t69
        IDX .t70, a, .t68
        ASSIGN .t70, 0
        ASSIGN .t71, 0
        MUL .t72, 1, 5
        ADD .t71, .t71, .t72
        IDX .t73, a, .t71
        ASSIGN .t73, 1
        ASSIGN .t74, 0
        MUL .t75, 1, 6
        ADD .t74, .t74, .t75
        IDX .t76, a, .t74
        ASSIGN .t76, 6
        ASSIGN .t77, 0
        MUL .t78, 1, 7
        ADD .t77, .t77, .t78
        IDX .t79, a, .t77
        ASSIGN .t79, 5
        ASSIGN .t80, 0
        MUL .t81, 1, 8
        ADD .t80, .t80, .t81
        IDX .t82, a, .t80
        ASSIGN .t82, 7
        ASSIGN .t83, 0
        MUL .t84, 1, 9
        ADD .t83, .t83, .t84
        IDX .t85, a, .t83
        ASSIGN .t85, 8
        DEF i
        ASSIGN i, 0
        DEF tmp
        ASSIGN tmp, 9
        ASSIGN .t86, 0
        IDX .t88, a, .t86
        ARR , .t88
        PARAM tmp
        PARAM i
        PARAM 
        CALL .t90, @QuickSort
        ASSIGN i, .t90
        GOTO .M24
.M24:
        LT .t91, i, n
        IF .t91 GOTO .M25
        GOTO .M26
.M25:
        DEF tmp
        ASSIGN .t92, 0
        MUL .t93, 1, i
        ADD .t92, .t92, .t93
        IDX .t94, a, .t92
        ASSIGN tmp, .t94
        PARAM tmp
        CALL .t95, @putint
        ASSIGN tmp, 10
        PARAM tmp
        CALL .t96, @putch
        ADD .t97, i, 1
        ASSIGN i, .t97
        GOTO .M24
.M26:
        ASSIGN .t98, 0
        GOTO .M27
.M27:
        RET .t98
        END
*/