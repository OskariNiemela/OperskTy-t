#include "array_operations.hh"



int suurin_v1(int *alkioptr, int koko)
{
    int biggest = 0;
    for(int* ptr=alkioptr;ptr<alkioptr+koko;ptr++)
    {
        if(*ptr > biggest)
        {
            biggest = *ptr;
        }
    }
    return biggest;
}

int suurin_v2(int *alkioptr, int *loppuptr)
{
    int biggest = 0;
    while(alkioptr!=loppuptr)
    {
        if(*alkioptr>biggest)
        {
            biggest = *alkioptr;
        }
        alkioptr++;
    }
    return biggest;
}

void kopioi(int *alkioptr, int *loppuptr, int *kohdeptr)
{

    while(alkioptr!=loppuptr)
    {
        *kohdeptr = *alkioptr;

        kohdeptr++;
        alkioptr++;
    }

}

void kaanna_takaperin(int *vasenptr, int *oikeaptr)
{
    int temp;
    oikeaptr--;
    while(vasenptr<oikeaptr)
    {
        temp = *vasenptr;
        *vasenptr = *oikeaptr;
        *oikeaptr = temp;
        vasenptr++;
        oikeaptr--;
    }
}
