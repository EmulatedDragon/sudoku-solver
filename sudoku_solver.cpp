#include<bits/stdc++.h>
using namespace std;
int sudoku[9][9][9],clone_sudoku[9][9][9],row,col,dep,i,j,k,s_x,s_y,buffer[9][9][9];
int charx=0,chary=0,dsudoku[9][9],inpflag=0;
void updatechar(int c);
void printdoku();
int input();
 //.................
void printdoku()
{
    cout<<"SUDOKU SOLVER"<<endl<<"USE wasd TO NAVIGATE , 1234 TO ENTER THE DESIRED NUMBER , E TO SOLVE IT"<<endl;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(i==chary && j==charx)
                cout<<'>'<<dsudoku[i][j]<<'<';
            else
                cout<<' '<<dsudoku[i][j]<<' ';
            cout<<' ';
        }
        cout<<"\n";
    }
}
 //.................
void updatechar(int c)
{
    if((c=='w'|| c=='W') && chary>0)
    {
        chary--;
    }
    if((c=='d'||c=='D')&& charx!=8)
    {
        charx++;
    }
    if((c=='s' || c=='S') && chary!=8 )
    {
        chary++;
    }
    if((c=='a'||c=='A' )&& charx>0)
    {
        charx--;
    }
    cout << "\033[2J\033[1;1H";
    printdoku();
}
 //.................
int input()
{
    char c;
    cin>>c;
    if((c-'0'>0 && c-'0'<10)||c=='w'||c=='w'||c=='s'||c=='a'||c=='d'||c=='W'||c=='S'||c=='A'||c=='D'||c=='e'||c=='E')
    {
        if(c=='e'||c=='E')
        {
            inpflag=1;
            return 0;
        }
        else
        {
            if(c=='w'||c=='w'||c=='s'||c=='a'||c=='d'||c=='W'||c=='S'||c=='A'||c=='D')
                updatechar(c);
            else
                {
                dsudoku[chary][charx]=c-'0';
                cout << "\033[2J\033[1;1H";
                printdoku();
                }
        }
        if(c=='e'||c=='E')
        {
            inpflag=1;
            return 0;
        }
    }
    else
        input();
}
 //.................
int num_of_non_0_elements(int row,int col)
    {
    int x=0;
    for (dep=0;dep<9;dep++)
        if (sudoku[row][col][dep]==0)
            x++;
    return (9-x);
    }
//...............
void update_rcs(int row, int col)
{
     int i,j,k,s_x,s_y;
     for(dep=0;dep<9;dep++)
         if (sudoku[row][col][dep]!=0)
            k=dep;
     for(i=0;i<9;i++)
        if(i!=row)
            sudoku[i][col][k]=0;
     for(j=0;j<9;j++)
         if(j!=col)
            sudoku[row][j][k]=0;
    s_x=row/3;
    s_y=col/3;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
        {
            if(i==row && j==col)
                continue;
            else
                if((i)/3==s_x && (j)/3==s_y)
                    sudoku[i][j][k]=0;
        }
}
//..................
void leave_one_element_row(int row,int dep)
{
    int temp;
    for(i=0;i<9;i++)
        if(sudoku[row][i][dep]==dep+1)
            temp=i;
    for(i=0;i<9;i++)
        {
        if(sudoku[row][temp][i]==dep+1)
            continue;
        else
           sudoku[row][temp][i]=0;
        }
}
//.....................
void leave_one_element_col(int col,int dep)
{
    int temp;
    for(i=0;i<9;i++)
        if(sudoku[i][col][dep]==dep+1)
            {temp=i;}
    for(i=0;i<9;i++)
        {
        if(sudoku[temp][col][i]==dep+1)
            continue;
        else
           sudoku[temp][col][i]=0;
        }
}
//..................
void leave_one_element_square(int s_x,int s_y,int dep)
{
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            if((i)/3==s_x && (j)/3==s_y)
                for(k=0;k<9;k++)
                    {
                    if(sudoku[i][j][k]==dep+1)
                        continue;
                     else
                        sudoku[i][j][k]=0;
                    }
}
//..................
void elimination()
{
    int i,j,k,sum=0;
    for(i=0;i<9;i++)
        for(k=0;k<9;k++)
        {
            sum=0;
            for(j=0;j<9;j++)
                sum=sum+sudoku[i][j][k];
            if(sum==k+1)
                leave_one_element_row(i,k);
        }
    for(j=0;j<9;j++)
        for(k=0;k<9;k++)
        {
            sum=0;
            for(i=0;i<9;i++)
                sum=sum+sudoku[i][j][k];
            if(sum==k+1)
                leave_one_element_col(j,k);
        }
    for(s_x=0;s_x<3;s_x++)
        for(s_y=0;s_y<3;s_y++)
            {
            for(k=0;k<9;k++)
                {
                sum=0;
                for(i=0;i<9;i++)
                    for(j=0;j<9;j++)
                        if((i)/3==s_x && (j)/3==s_y)
                            sum=sum+sudoku[i][j][k];
                }
            if(sum==k+1)
                leave_one_element_square(s_x,s_y,k);
            }
}
//.................
int check_saturation()
{
    int temp=0;
    for(row=0;row<9;row++)
        for(col=0;col<9;col++)
            for(dep=0;dep<9;dep++)
                if(buffer[row][col][dep]!=sudoku[row][col][dep])
                    {temp++;
                    buffer[row][col][dep]=sudoku[row][col][dep];}
    if(temp==0)
        return 1;
    else
        return 0;
}
//..................
void input_for_update_rcs()
{
    static int breaking_point=0;
    for(row=0;row<9;row++)
        for(col=0;col<9;col++)
            if(num_of_non_0_elements(row,col)==1)
                {
                breaking_point++;
                update_rcs(row,col);
                }
    elimination();
}
//...........
void exchange()
{
    int temp;
    for(row=0;row<9;row++)
        for(col=0;col<9;col++)
        {
            temp=dsudoku[row][col];
            if(temp!=0)
                for(dep=0;dep<9;dep++)
                    if (sudoku[row][col][dep]!=temp)
                        sudoku[row][col][dep]=0;
        }
}
//.............
int win()
{
    int temp=0;
    for(row=0;row<9;row++)
        for(col=0;col<9;col++)
            if (num_of_non_0_elements(row,col)==1)
                temp++;
    if (temp==81)
        return 1;
    else
        return 0;
}
//......................
void print_sudoku()
{
    for(row=0;row<9;row++)
    {
        for(col=0;col<9;col++)
        {
            for(dep=0;dep<9;dep++)
                if (sudoku[row][col][dep]!=0)
                    printf(" %d ",sudoku[row][col][dep]);
            printf(" ");
        }
        printf("\n");
    }
}
//......................
void solve_sudoku()
{
    while(win()==0 && check_saturation()==0)
        input_for_update_rcs();
}
//............
void clone_sudoku_function(int sudoku[][9][9],int clone_sudoku[][9][9])
{
    for(row=0;row<9;row++)
        for(col=0;col<9;col++)
            for(dep=0;dep<9;dep++)
                clone_sudoku[row][col][dep]=sudoku[row][col][dep];
}
//............
int check_sudoku()
{
    int count=0,flag=0;
    for(row=0;row<9;row++)
        for(col=0;col<9;col++)
            {
            count=0;
            for(dep=0;dep<9;dep++)
                if (sudoku[row][col][dep]!=0)
                    count++;
            if (count==0)
                flag=1;
            }
    if (flag==1)
        return 1;
    else
        return 0;
}
//........................
int check_rcs()
{
    int i,j,k,l,count;
    for(l=1;l<=9;l++)
        for(i=0;i<9;i++)
        {
            count=0;
            for(j=0;j<9;j++)
            {
                if(num_of_non_0_elements(i,j)==1)
                    for(k=0;k<9;k++)
                        if(sudoku[i][j][k]==l)
                            count++;
            if(count>1)
                return 0;
            }
        }
    for(l=1;l<=9;l++)
        for(j=0;j<9;j++)
        {
            count=0;
            for(i=0;i<9;i++)
                if(num_of_non_0_elements(i,j)==1)
                    for(k=0;k<9;k++)
                        if(sudoku[i][j][k]==l)
                            count++;
            if(count>1)
                return 0;
        }
    return 1;
}
//.................
void input_for_brute_force();
void brute_force(int rc)
{
    int x,y,i=0,j,k,num[9]={0,0,0,0,0,0,0,0,0},n;
    static int flag=0;
    x=rc/10;
    y=rc%10;
    for(k=0;k<9;k++)
        if(sudoku[x][y][k]!=0)
        {
            num[i]=k+1;
            i++;
        }
    if(flag==0)
    {
        clone_sudoku_function(sudoku,clone_sudoku);
        flag++;
    }
    for(j=0;j<i;j++)
    {
        n=num[j];
        for(k=0;k<9;k++)
            if(sudoku[x][y][k]!=n)
                sudoku[x][y][k]=0;
        solve_sudoku();
        if(win()==1 && check_rcs()==1)
            return;
        if(check_sudoku()==1 || check_rcs()==0)
        {
            clone_sudoku[x][y][n-1]=0;
            clone_sudoku_function(clone_sudoku,sudoku);
        }
        if(check_sudoku()==0 && check_rcs()==1)
            input_for_brute_force();
    }
    if(j==i && win()==0)
        input_for_brute_force();
}
//....................
void input_for_brute_force()
{
    int i,j,min,num;
    min=9;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            if(num_of_non_0_elements(i,j)<min && num_of_non_0_elements(i,j)>1)
            {
                min=num_of_non_0_elements(i,j);
                row=i;
                col=j;
            }
    num=(row*10)+col;
    brute_force(num);
}
//................
int main()
{
    for(row=0;row<9;row++)
        for(col=0;col<9;col++)
            for(dep=0;dep<9;dep++)
                sudoku[row][col][dep]=dep+1;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            dsudoku[i][j]=0;
        }
    }
    printdoku();
    while(inpflag==0)
    {
        input();
    }    
    exchange();
    solve_sudoku();
    if(check_saturation()==1)
        input_for_brute_force();
    print_sudoku();
    cout<<endl<<"GG";
    return 0;
}
//......................
//0 5 1 2 0 0 0 9 0 0 3 8 0 7 9 0 4 0 2 9 0 5 0 0 0 0 6 1 2 3 6 0 0 7 0 0 8 7 0 3 0 1 0 5 4 0 0 9 0 0 8 3 6 1 4 0 0 0 0 2 0 1 5 0 1 0 8 6 0 4 3 0 0 6 0 0 0 7 9 2 0
//0 9 0 0 0 7 0 0 0 0 7 0 0 0 0 0 0 8 0 3 4 2 9 0 5 0 0 9 2 8 3 0 0 0 6 0 0 0 0 6 0 9 0 0 0 0 1 0 0 0 2 8 3 9 0 0 1 0 2 6 3 5 0 7 0 0 0 0 0 0 1 0 0 0 0 1 0 0 0 8 0
//8 7 6 0 0 0 0 0 4 0 0 3 0 0 2 0 0 0 0 0 0 0 7 0 1 0 9 0 5 0 4 0 0 3 0 0 0 3 0 0 0 0 0 1 0 0 0 1 0 0 9 0 5 0 3 0 5 0 2 0 0 0 0 0 0 0 7 0 0 6 0 0 4 0 0 0 0 3 0 7 8
//0 1 0 7 0 0 0 2 4 0 0 0 0 9 0 0 0 3 0 0 7 0 0 0 0 5 0 0 0 0 1 0 5 0 6 0 0 0 1 0 3 0 7 0 0 0 7 0 2 0 8 0 0 0 0 2 0 0 0 0 9 0 0 1 0 0 0 5 0 0 0 0 6 9 0 0 0 2 0 3 0
//hardest sudoku not working cuz of limited computational power-8 0 0 0 0 0 0 0 0 0 0 3 6 0 0 0 0 0 0 7 0 0 9 0 2 0 0 0 5 0 0 0 7 0 0 0 0 0 0 0 4 5 7 0 0 0 0 0 1 0 0 0 3 0 0 0 1 0 0 0 0 6 8 0 0 8 5 0 0 0 1 0 0 9 0 0 0 0 4 0 0
//2 0 0 5 0 0 8 0 1 0 0 7 0 0 6 0 0 0 0 8 0 0 4 0 0 0 9 6 0 0 1 0 0 0 9 0 0 0 4 0 0 0 1 0 0 0 2 0 0 0 7 0 0 6 1 0 0 0 9 0 0 5 0 0 0 0 6 0 0 3 0 0 7 0 5 0 0 8 0 0 2
//0 0 9 3 0 6 5 0 0 0 0 0 0 0 0 0 0 0 2 0 7 0 0 0 9 0 4 3 0 0 0 8 0 0 0 7 0 0 0 2 0 1 0 0 0 8 0 0 0 4 0 0 0 5 4 0 6 0 0 0 2 0 3 0 0 0 0 0 0 0 0 0 0 0 1 7 0 4 6 0 0
//0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//0 6 0 0 0 0 0 3 0 3 0 0 9 0 1 0 0 4 0 0 5 0 2 0 1 0 0 0 2 0 0 0 0 0 4 0 0 0 8 0 5 0 7 0 0 0 9 0 0 0 0 0 8 0 0 0 4 0 8 0 6 0 0 6 0 0 1 0 2 0 0 3 0 5 0 0 0 0 0 7 0