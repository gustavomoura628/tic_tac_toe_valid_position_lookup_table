#include <bits/stdc++.h>
using namespace std;

int THE_TABLE[19683] = { 0 };

const int SIZE_OF_BITPACKED_TABLE = 19683/(sizeof(unsigned int)*8)+1;
unsigned int bit_packed_table[SIZE_OF_BITPACKED_TABLE] = { 0 };

void print_table(int * table)
{
    for(int i=0;i<9;i++)
    {
        switch(table[i])
        {
            case 0:
                cout << '.';
                break;
            case 1:
                cout << 'X';
                break;
            case 2:
                cout << 'O';
                break;
        }
        cout << ' ';
        if(i%3==2) cout << '\n';
    }
}

int table_to_number(int * table)
{
    int number = 0;
    int power_of_three = 1;
    for(int i=0;i<9;i++)
    {
        number += table[i]*power_of_three;
        power_of_three*=3;
    }
    return number;
}

void flip_table(int * table)
{
    swap(table[0],table[2]);
    swap(table[3],table[5]);
    swap(table[6],table[8]);
}

void rotate_table(int * table)
{
    swap(table[1],table[5]);
    swap(table[1],table[7]);
    swap(table[1],table[3]);
    
    swap(table[0],table[2]);
    swap(table[0],table[8]);
    swap(table[0],table[6]);
}

int smallest_table_representation(int * table)
{
    int table_c[9];
    memcpy(table_c, table, 9*sizeof(int));

    int smallest = table_to_number(table_c);
    rotate_table(table_c);
    smallest = min(smallest, table_to_number(table_c));
    rotate_table(table_c);
    smallest = min(smallest, table_to_number(table_c));
    rotate_table(table_c);
    smallest = min(smallest, table_to_number(table_c));
    flip_table(table_c);
    smallest = min(smallest, table_to_number(table_c));
    rotate_table(table_c);
    smallest = min(smallest, table_to_number(table_c));
    rotate_table(table_c);
    smallest = min(smallest, table_to_number(table_c));
    rotate_table(table_c);
    smallest = min(smallest, table_to_number(table_c));
    return smallest;
}

bool has_someone_won(int * table)
{
    if( table[0] != 0 &&  table[0] == table[1] && table[1] == table[2] ) return true;
    if( table[3] != 0 &&  table[3] == table[4] && table[4] == table[5] ) return true;
    if( table[6] != 0 &&  table[6] == table[7] && table[7] == table[8] ) return true;


    if( table[0] != 0 &&  table[0] == table[3] && table[3] == table[6] ) return true;
    if( table[1] != 0 &&  table[1] == table[4] && table[4] == table[7] ) return true;
    if( table[2] != 0 &&  table[2] == table[5] && table[5] == table[8] ) return true;


    if( table[0] != 0 &&  table[0] == table[4] && table[4] == table[8] ) return true;
    if( table[2] != 0 &&  table[2] == table[4] && table[4] == table[6] ) return true;

    return false;
}

int STEPS = 0;

void dfs_play_tic_tac_toe(int * table, int turn)
{
    STEPS++;
    if(STEPS%2000000==0) cerr << "Progress = " << STEPS/87208051.0*100 << "%" << endl;
    THE_TABLE[smallest_table_representation(table)] = 1;
    //print_table(table);
    //cout << "STEPS = " << STEPS << '\n';
    if(has_someone_won(table)) return;

    for(int i=0;i<9;i++)
    {
        if(table[i] == 0)
        {
            table[i] = turn;
            dfs_play_tic_tac_toe(table, 3-turn);// Other player's turn
            table[i] = 0;
        }
    }
}

int unpack_bit_packed_table(unsigned int * bit_packed_table, int index)
{
    int SIZE_OF_VARIABLE_IN_BYTES = sizeof(bit_packed_table[0]);
    int bpi = index/(SIZE_OF_VARIABLE_IN_BYTES*8);
    int bpj = index%(SIZE_OF_VARIABLE_IN_BYTES*8);
    return (bit_packed_table[bpi]&(1<<bpj))!=0;
}

int main(){
    int table[9];
    for(int i=0;i<9;i++)table[i] = 0;
    dfs_play_tic_tac_toe(table,1);
    cerr << "STEPS = " << STEPS << '\n';
    cout << "int THE_TABLE[19683]=         {";
    for(int i=0;i<19683;i++)
    {
        cout << THE_TABLE[i];
        if(i<19682)cout << ",";
    }
    cout << "};\n";

    cout << "int bit_packed_table[2461] = {";
    int SIZE_OF_VARIABLE_IN_BYTES = sizeof(bit_packed_table[0]);
    for(int i=0;i<SIZE_OF_BITPACKED_TABLE;i++)
    {
        int bit_pos=0;
        for(int j=i*SIZE_OF_VARIABLE_IN_BYTES*8;j<(i+1)*SIZE_OF_VARIABLE_IN_BYTES*8 && j<19683;j++)
        {
            bit_packed_table[i]|=THE_TABLE[j]<<bit_pos;
            bit_pos++;
        }
        cout << bit_packed_table[i];
        if(i<SIZE_OF_BITPACKED_TABLE-1)cout << ",";
    }
    cout << "};\n";
    cout << "int THE_TABLE_UNPACKED[19683]={";
    for(int i=0;i<19683;i++)
    {
        cout << unpack_bit_packed_table(bit_packed_table,i);
        if(i<19682)cout << ",";
    }
    cout << "};\n";

    return 0;
}
