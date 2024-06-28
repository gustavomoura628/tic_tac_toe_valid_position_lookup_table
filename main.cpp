#include <bits/stdc++.h>
using namespace std;
// Bit packed lookup table of all possible and impossible game positions
const int SIZE_OF_BITPACKED_TABLE = 19683/(sizeof(unsigned int)*8)+1;
unsigned int bit_packed_table[SIZE_OF_BITPACKED_TABLE] = {84139,2148889671,298455125,1611923716,887439417,331880,866645,52,2152792064,3549779492,0,2483552384,703011,149225472,179359874,2,0,577,0,679690240,0,0,0,351504,3221240160,1476395060,2717909006,44859392,216656,11168,538198146,2281734201,179970962,10616864,169869312,2721651888,738363562,110930599,2418336849,3275930147,2296645674,2953454216,441494172,2692909092,134618242,10,256,12,54525952,11010048,0,0,32,221844736,3266218212,956435104,8956578,2559214860,548015110,10953376,268437122,2696937508,522,2189959168,110922368,6664,2181038080,6,0,0,0,0,0,0,0,0,0,2349342722,10920,0,1916807168,0,537169930,6770,0,10619904,0,2281701376,328,0,532480,0,0,0,0,0,0,0,0,133120,1073741824,114,0,21233664,336896,1073762560,673349973,1916807178,6932640,1075089416,297878528,2492073041,1162113028,17104896,0,0,0,0,0,0,0,0,648,28,85983232,1048576,65536,32,80,34217984,1208872,2281701448,1148191892,68157701,294912,4277248,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,73728,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2147483648,1073743912,65,307232768,17825792,262144,18,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,65536,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,149504,33280,2147484298,32,86245376,532608,84224,292,0,344981504,0,0,16640,1073741824,1359020048,0,0,82,0,1074003968,0,0,320,576,160,142606336,20971520,0,2048,0,2684485632,86245376,299008,84224,64,20971537,335560704,1048576,2147484288,268436500,85983232,272695296,16384,0,4176,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,642,0,0,0,0,520,0,0,0,0,0,0,0,0,0,0,288,64,272629761,0,131072,1024,0,262144,21037056,66816,64,134218386,1048578,163840,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,268435456,0,0,8192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,2097152,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int unpack_bit_packed_table(unsigned int * bit_packed_table, int index)
{
    int SIZE_OF_VARIABLE_IN_BYTES = sizeof(bit_packed_table[0]);
    int bpi = index/(SIZE_OF_VARIABLE_IN_BYTES*8);
    int bpj = index%(SIZE_OF_VARIABLE_IN_BYTES*8);
    return (bit_packed_table[bpi]&(1<<bpj))!=0;
}

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

bool is_valid_position(int *table)
{
    return unpack_bit_packed_table(bit_packed_table, smallest_table_representation(table))==1;
}

int main(){
    int n;
    cin >> n;
    int table[9];
    char c;
    for(int k=0;k<n;k++)
    {
        for(int i=0;i<9;i++)
        {
            cin >> c;
            //cout << "CHAR WAS {" << c << "}\n";
            switch(c)
            {
                case '.':
                    table[i] = 0;
                    break;
                case 'X':
                    table[i] = 1;
                    break;
                case 'O':
                    table[i] = 2;
            }
        }

        //print_table(table);
        //cout << "table_number = " << table_to_number(table) << '\n';
        //cout << "smallest_table_representation = " << smallest_table_representation(table) << '\n';
        //cout << "is_valid_position = " << (is_valid_position(table)? "yes" : "no") << '\n';
        cout << (is_valid_position(table)? "yes" : "no") << '\n';
    }

    return 0;
}

