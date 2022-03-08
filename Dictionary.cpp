#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <windows.h>
#define M 100
using namespace std;
struct TuDien
{
    char Anh[M];
    char Viet[M];
    char Loai[M];
};
struct Node
{
    TuDien Data;
    Node *L;
    Node *R;
};
typedef Node *Pnode;
void Init(Pnode &T)
{
    T = NULL;
}
int Empty(Pnode T)
{
    if (T == NULL)
        return 1;
    return 0;
}
Pnode GetNode(TuDien x)
{
    Pnode p = new Node;
    p->Data = x;
    p->L = p->R = NULL;
    return p;
}
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };  
    SetConsoleCursorPosition(h,c);
}
//Ham them tu moi vao cay nhi phan
void InputA1(Pnode &T, TuDien x)
{
    if (Empty(T) == 1)
    {
        T = GetNode(x);
    }

    else
    {
        if (strcmp(x.Anh, T->Data.Anh) < 0)
            InputA1(T->L, x);
        else
            InputA1(T->R, x);
    }
}
//Chuc nang them tu tieng Anh vao tu dien
void InputA(Pnode &T, TuDien x)
{
    if (Empty(T) == 1)
    {
        T = GetNode(x);
    }
    else
    {
    H:
        if (strcmp(x.Anh, T->Data.Anh) == 0)
        {
            cout << "\nTu Nay Da Co, Moi Nhap Lai ";
            cout << "\nNhap Tu Can Them (Khong Nhap Nua Thi An phim Enter) ";
            gets(x.Anh);
            if (strcmp(x.Anh, "") == 0)
                return;
            cout << "Nhap Nghia: ";
            gets(x.Viet);
            cout << "Nhap Loai Tu: ";
            gets(x.Loai);
            goto H;
        }

        else
        {
            if (strcmp(x.Anh, T->Data.Anh) < 0)
                InputA(T->L, x);
            else
                InputA(T->R, x);
        }
    }
}

//Nhap tu tieng Anh can them tu ban phim
void InA(Pnode &T, TuDien x)
{
    do
    {
        cout << "\nNhap Tu Can Them (Khong Nhap Nua Thi An phim Enter) ";
        gets(x.Anh);
        if (strcmp(x.Anh, "") == 0)
            return;
        cout << "Nhap Nghia: ";
        gets(x.Viet);
        cout << "Nhap Loai Tu: ";
        gets(x.Loai);
        InputA(T, x);
    } while (strcmp(x.Anh, "") != 0);
}

//Ghi tu tieng Anh da nhap vao file
void WriteA(Pnode &T)
{
    FILE *f;
    f = fopen("D:\\Dictionary\\TuDienA.txt", "a");
    if (T != NULL)
    {
        fwrite(&T->Data, sizeof(TuDien), 1, f);
        //fwrite(&T->Data.Viet,sizeof(TuDien),1,f);
        //fwrite(&T->Data.Loai,sizeof(TuDien),1,f);
        WriteA(T->L);
        WriteA(T->R);
    }
    fclose(f);
}

//Doc tu tieng Anh da nhap co trong file
void ReadA(Pnode &T, TuDien x)
{
    FILE *f;
    f = fopen("D:\\Dictionary\\TuDienA.txt", "r");
    if (f == NULL)
    {
        cout << "\nMo Bi Loi";
        return;
    }
    do
    {
        fread(&x, sizeof(TuDien), 1, f);
        if (!feof(f))
        {
            InputA1(T, x);
        }
        else
            break;
    } while (1);
    fclose(f);
}

//Tim kiem tu tieng Anh can biet nghia
void TraTuA(Pnode T, TuDien x)
{
    char p;
    if (T != NULL)
    {
        if (strcmp(T->Data.Anh, x.Anh) == 0)
        {
            cout << "Nghia Cua Tu: " << T->Data.Viet;
            cout << "\nLoai Cua Tu: " << T->Data.Loai;
            return;
        }
        if (strcmp(T->Data.Anh, x.Anh) > 0)
            TraTuA(T->L, x);
        else
            TraTuA(T->R, x);
    }
    else
        cout << "Khong Tim Duoc Tu Can Tra";
}

//Tim tu can tra trong cay nhi phan
Pnode Search(Pnode T, TuDien x)
{
    Pnode p = T;
    while (p != NULL)
    {
        if (strcmp(x.Anh, p->Data.Anh) == 0)
            return p;
        else
        {
            if (strcmp(x.Anh, p->Data.Anh) < 0)
                p = p->L;
            else
                p = p->R;
        }
    }
    return NULL;
}
void SearchF(Pnode &p, Pnode &q)
{
    if (q->L)
        SearchF(p, q->L);
    else
    {
        p->Data = q->Data;
        p = q;
        q = q->L;
    }
}

//Xoa tu tieng Anh co trong tu dien
int Del(Pnode &T, TuDien x)
{
    if (T == NULL)
    {
        cout << "\nTu Dien Trong";
        return 0;
    }
    if (Search(T, x) != NULL)
    {
        if (strcmp(T->Data.Anh, x.Anh) > 0)
            Del(T->L, x);
        if (strcmp(T->Data.Anh, x.Anh) < 0)
            Del(T->R, x);
        Pnode p = T;
        if (T->L == NULL)
            T = T->R;
        else if (T->R == NULL)
            T = T->L;
        else
        {
            SearchF(p, T->R);
            delete p;
        }
        return 1;
    }
    else
    {
        cout << "\nKhong Tim Thay Du Lieu";
        return 0;
    }
}

/*================================================= =======*/

//Them tu tieng Viet vao cay nhi phan
void InputV1(Pnode &T, TuDien x)
{
    if (Empty(T) == 1)
    {
        T = GetNode(x);
    }

    else
    {
        if (strcmp(x.Viet, T->Data.Viet) < 0)
            InputV1(T->L, x);
        else
            InputV1(T->R, x);
    }
}

//Chuc nang them tu tieng Viet vao tu dien
void InputV(Pnode &T, TuDien x)
{
    if (Empty(T) == 1)
    {
        T = GetNode(x);
    }
    else
    {

    H:
        if (strcmp(x.Viet, T->Data.Viet) == 0)
        {
            cout << "\nTu Nay Da Co, moi Ban Nhap Lai: ";
            cout << "\nTu Can Them: ";
            gets(x.Viet);
            cout << "Nghia Cua Tu: ";
            gets(x.Anh);
            cout << "Loai Cua Tu: ";
            gets(x.Loai);
            goto H;
        }
        else
        {
            if (strcmp(x.Viet, T->Data.Viet) < 0)
                InputV(T->L, x);
            else
                InputV(T->R, x);
        }
    }
}

//Nhap tu tieng Viet can them tu ban phim
void InV(Pnode &T, TuDien x)
{
    do
    {
        cout << "\nNhap Tu Can Them (Khong Nhap Nua Thi An phim Enter) ";
        gets(x.Viet);
        if (strcmp(x.Viet, "") == 0)
            return;
        cout << "Nhap Nghia: ";
        gets(x.Anh);
        cout << "Nhap Loai Tu: ";
        gets(x.Loai);
        InputV(T, x);
    } while (strcmp(x.Viet, "") != 0);
}

//Ghi tu tieng Viet da nhap vao file
void WriteV(Pnode &T)
{
    FILE *f;
    f = fopen("D:\\Dictionary\\TuDienV.txt", "a");
    if (T != NULL)
    {
        fwrite(&T->Data, sizeof(TuDien), 1, f);
        //fwrite(&T->Data.Anh,sizeof(TuDien),1,f);
        //fwrite(&T->Data.Loai,sizeof(TuDien),1,f);
        WriteV(T->L);
        WriteV(T->R);
    }
    fclose(f);
}

//Doc du lieu tu tieng Viet da co trong file
void ReadV(Pnode &T, TuDien x)
{
    FILE *f;
    f = fopen("D:\\Dictionary\\TuDienV.txt", "r");
    if (f == NULL)
    {
        cout << "\nMo Bi Loi";
        return;
    }
    do
    {
        fread(&x, sizeof(TuDien), 1, f);
        if (!feof(f))
        {
            InputV1(T, x);
        }
        else
            break;
    } while (1);
    fclose(f);
}

//Chuc nang tra cuu tu tieng Viet
void TraTuV(Pnode T, TuDien x)
{
    if (T != NULL)
    {
        if (strcmp(T->Data.Viet, x.Viet) == 0)
        {
            cout << "Nghia Cua Tu: " << T->Data.Anh;
            cout << "\nLoai Cua Tu: " << T->Data.Loai;
            return;
        }
        if (strcmp(T->Data.Viet, x.Viet) > 0)
            TraTuV(T->L, x);
        else
            TraTuV(T->R, x);
    }
    else
        cout << "Khong Tim Duoc Tu Can Tra";
}

//Tim kiem tu tieng Viet trong cay nhi phan
Pnode SearchV(Pnode T, TuDien x)
{
    Pnode p = T;
    while (p != NULL)
    {
        if (strcmp(x.Viet, p->Data.Viet) == 0)
            return p;
        else
        {
            if (strcmp(x.Viet, p->Data.Viet) < 0)
                p = p->L;
            else
                p = p->R;
        }
    }
    return NULL;
}

//Xoa tu tieng Viet co trong file
int DelV(Pnode &T, TuDien x)
{
    if (T == NULL)
    {
        cout << "\nTu Dien Trong";
        return 0;
    }
    if (Search(T, x) != NULL)
    {
        if (strcmp(T->Data.Viet, x.Viet) > 0)
            Del(T->L, x);
        if (strcmp(T->Data.Viet, x.Viet) < 0)
            Del(T->R, x);
        Pnode p = T;
        if (T->L == NULL)
            T = T->R;
        else if (T->R == NULL)
            T = T->L;
        else
        {
            SearchF(p, T->R);
            delete p;
        }
        return 1;
    }
    else
    {
        cout << "\nKhong Tim Thay Du Lieu";
        return 0;
    }
}
/*==========================================================*/

//Menu tu dien Anh-Viet
void menu1()
{
    Pnode T;
    Init(T);
    TuDien x;
    ReadA(T, x);
    char chon;
    do
    {
        system("cls");
        cout << "\n\t\t\t====Tu-Dien-Anh-Viet====";
        cout << "\nNhan Phim ESC De Thoat";
        cout << "\nPhim 1: Them Tu";
        cout << "\nPhim 2: Tra Mot Tu";
        cout << "\nPhim 3: Xoa Mot Tu";
        chon = getch();
        system("cls");
        switch (chon)
        {
        case 27:
        t:
            cout << "\nBan Co Muon Luu Khong (y/n)";
            char a;
            a = getch();
            if (a == 'y')
            {
                unlink("D:\\Dictionary\\TuDienA.txt");
                WriteA(T);
                cout << "\nLuu Thanh Cong!";
                getch();
                break;
            }
            if (a == 'n')
                break;
            else
                goto t;

        case '1':
            InA(T, x);
            break;
        case '2':
            cout << "\nNhap Tu Can Tra: ";
            gets(x.Anh);
            TraTuA(T, x);
            getch();
            break;
        case '3':
            cout << "\nNhap Tu Can Xoa: ";
            gets(x.Anh);
            Del(T, x);
            cout << "\nThao Tac Hoan Thanh!";
            getch();
            break;
        default:
            cout << "\nCo Dau Ma An, An Lai Di :D";
            getch();
            break;
        }
    } while (chon != 27);
}

//Menu tu dien Viet-Anh
void menu2()
{
    Pnode T;
    Init(T);
    TuDien x;
    ReadV(T, x);
    char chon;
    do
    {
        system("cls");
        cout << "\n\t\t\t====Tu-Dien-Viet-Anh====";
        cout << "\nNhan Phim ESC De Thoat";
        cout << "\nPhim 1: Them Tu";
        cout << "\nPhim 2: Tra Mot Tu";
        cout << "\nPhim 3: Xoa Mot Tu";
        chon = getch();
        system("cls");
        switch (chon)
        {
        case 27:
        t:
            cout << "\nBan Co Muon Luu Khong (y/n)";
            char a;
            a = getch();
            if (a == 'y')
            {
                unlink("D:\\Dictionary\\TuDienV.txt");
                WriteV(T);
                cout << "\nLuu Thanh Cong!";
                getch();
                break;
            }
            if (a == 'n')
                break;
            else
                goto t;
        case '1':
            InV(T, x);
            break;
        case '2':
            cout << "\nNhap Tu Can Tra: ";
            gets(x.Viet);
            TraTuV(T, x);
            getch();
            break;
        case '3':
            cout << "\nNhap Tu Can Xoa: ";
            gets(x.Viet);
            DelV(T, x);
            cout << "\nThao Tac Hoan Thanh!";
            getch();
            break;
        default:
            cout << "\nCo Dau Ma An, An Lai Di :D";
            getch();
            break;
        }
    } while (chon != 27);
}

//Menu chinh cua chuong trinh
void menu()
{
    system("cls");
    gotoxy(24,13);
    cout << "An ALT + ENTER De Chay Tot Chuong Trinh";
    Sleep(3000);
    system("cls");
    gotoxy(30, 13);
    cout << "An Phim Bat Ky De Tiep Tuc";
    getch();
    system("cls");
    gotoxy(18, 13);
    cout << "================================================";
    gotoxy(31, 12);
    cout << "DANG XU LY DU LIEU";
    gotoxy(18, 13);
    char a[50] = "|||||||||||||||||||||||||||||||||||||||||||||||||";
    for (int i = 1; i < 49; i++)
    {
        cout << a[i];
        Sleep(40);
    }
    gotoxy(34, 14);
    cout << "Da Xu Ly Xong!";
    Sleep(500);
    char chon;
    do
    {
        system("cls");
        cout << "\n\t\t\t====MENU CHINH CUA CHUONG TRINH====";
        cout << "\nNhan Phim ESC De Thoat";
        cout << "\nPhim 1: Tu Dien Anh-Viet";
        cout << "\nPhim 2: Tu Dien Viet-Anh";
        chon = getch();
        system("cls");
        switch (chon)
        {
        case 27:
            break;
        case '1':
            menu1();
            break;
        case '2':
            menu2();
            break;
        default:
            break;
        }
    } while (chon != 27);
}
int main()
{
    menu();
}
