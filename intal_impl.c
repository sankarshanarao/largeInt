#include<string.h>
#include<stdlib.h>
#include<math.h>
#define NodeSize 9

typedef struct largeInt
{
    long long int * nums;
    long int len;

}largeInt;

char * stripLeadingZeros(char * str);
int isZero(largeInt*hint);

void* intal_create(char* stri)
{
    char * str = stripLeadingZeros(stri);
    largeInt*newNum = (largeInt*)malloc(sizeof(largeInt));
    int strle = strlen(str);
    newNum->len = strle/NodeSize+1;
    newNum->nums = (long long int*)malloc(sizeof(long long int)*newNum->len);

    long int i;
    int j,k=0,oddLen=strle%NodeSize;
    char part[NodeSize+1];
    part[NodeSize]='\0';

    j=NodeSize-1;
    for(i=strle-1;i>=0;--i)
    {
        part[j--]=str[i];
        if(j==-1)
        {
            //printf("\n%s\n",part);
            newNum->nums[k++]=atoll(part);
            j=NodeSize-1;
        }
    }
    for(i=0;i<NodeSize-oddLen;++i)
        part[i]='0';

    newNum->nums[k]=atoll(part);
    //printf("\n%s\n",part);


    return newNum;
}

void intal_destroy(void* intal)
{
    largeInt * toDes = intal;
    free(toDes->nums);
    free(toDes);
}

char * stripLeadingZeros(char * str)
{
    int i,j=strspn(str,"0");
    //printf("\n%d zeros\n",j);
    char * newS = (char*)malloc(sizeof(char)*(strlen(str)-j+1));
    for(i=j;str[i]!='\0';i++)
    {
        newS[i-j]=str[i];
    }
    newS[i-j]='\0';
    return newS;
}

char * normToZero(char*num)
{
    char * newS = (char*)malloc(sizeof(char)*(NodeSize+1));
    int i,j;
    for(i=0;i<NodeSize-strlen(num);++i)
    {
        newS[i]='0';
    }
    for(j=0;j<strlen(num);++j)
    {
        newS[i++]=num[j];
    }
    newS[i]='\0';


    return newS;
}

char* intal2str(void* intal)
{
    largeInt*toStr = intal;
    if(isZero(intal))
       return "0";
    char * str = (char *)malloc(sizeof(char)*toStr->len*NodeSize);
    str[0]='\0';
    char nn[NodeSize+1];
    nn[NodeSize]='\0';
    long int i;
    for(i=toStr->len-1;i>=0;--i)
    {

        strcat(str,normToZero(ltoa(toStr->nums[i],nn,10)));
        //printf("%lld",toStr->nums[i]);
    }
    str = stripLeadingZeros(str);
    return str;
}

int intal_compare(void* intal1, void* intal2)
{
    largeInt *a = intal1, *b = intal2;
    long int i;
    if(a->len != b->len)
    {
        if(a->len > b->len)
        {
            return -1;
        }
        else return 1;
    }
    else
    {
        for(i=a->len-1;i>=0;--i)
        {
            if(a->nums[i]!=b->nums[i])
            {
                if(a->nums[i]>b->nums[i])
                {
                    return -1;
                }
                else
                    return 1;
            }
        }
    }
    return 0;
}



void intal_increment(void* intal)
{
        largeInt*incrNum = intal;
        int i,carry=1;
        long long int power = pow(10,NodeSize);
        for(i=0;i<incrNum->len;++i)
        {
            incrNum->nums[i]+=carry;
            carry = incrNum->nums[i]/power;
            incrNum->nums[i]%=power;
            if(carry == 0)
            {
                break;
            }
        }
        if(carry==1)
        {
            incrNum->nums = realloc(incrNum->nums,++incrNum->len);
            incrNum->nums[incrNum->len-1]=1;
        }
}

int isZero(largeInt*hint)
{
    for(int i=0;i<hint->len;i++)
    {
        if(hint->nums[i]!=0)
            return 0;
    }
    return 1;
}

void intal_decrement(void* intal)
{
        if(isZero(intal))
            return;
        largeInt*decrNum = intal;
        int i;
       long long int power = pow(10,NodeSize)-1;
        for(i=0;i<decrNum->len;i++)
        {
            //printf("%lld,",decrNum->nums[i]);
            if(decrNum->nums[i]==0)
            {

                decrNum->nums[i]=power;
                //printf("Zero:%lld",decrNum->nums[i]);
                //getch();
            }
            else
            {
                //printf("NonZero");
                //getch();
                --decrNum->nums[i];
                break;

            }

        }
        //printf("Done");
        //getch();
}

void* intal_add(void* intal1, void* intal2)
{
    largeInt *a=(largeInt*)intal1,*b=(largeInt*)intal2;
    largeInt *c=(largeInt*)malloc(sizeof(largeInt));

    //printf("\n%ld,%ld\n",a->len,b->len);

    if(a->len > b->len)
        c->len = a->len + 1;
    else
        c->len = b->len +1;

    //printf("%ld\n",c->len);

    c->nums = (long long *)malloc(sizeof(long long)*c->len);
   long long int power = pow(10,NodeSize);

    int i,carry=0;

    for(i=0;i<a->len;++i)
    {
        c->nums[i]=a->nums[i];
    }

    for(i=0;i<b->len;i++)
    {
        c->nums[i] += b->nums[i];
    }

    carry = 0;

    for(i=0;i<c->len;++i)
    {
        c->nums[i]+=carry;
        carry = c->nums[i]/power;
        c->nums[i]%=power;
    }

    //printf("\n%s",intal2str(c));

    return c;
}

void* intal_diff(void* intal1, void* intal2)
{
    largeInt *a,*b;
    if(intal_compare(intal1,intal2)==1)
    {
        a = (largeInt*)intal2;
        b = (largeInt*)intal1;
    }
    else
    {
        a = (largeInt*)intal1;
        b = (largeInt*)intal2;
    }
    largeInt *c=(largeInt*)malloc(sizeof(largeInt));

    //printf("\n%ld %ld\n",a->len,b->len);

    c->len = a->len+1;

    //printf("%ld",c->len);

    c->nums = (long long *)malloc(sizeof(long long)*c->len);
   long long int power = pow(10,NodeSize);

    int i,carry=0;

    for(i=0;i<a->len;++i)
    {
        c->nums[i]=a->nums[i];
    }

    for(i=0;i<b->len;i++)
    {
        c->nums[i] -= b->nums[i];
    }

    carry = 0;

    for(i=0;i<c->len;++i)
    {
        if(c->nums[i]<0)
        {
            c->nums[i]+=power;
            carry = 1;
        }
        else
        {
            if(carry==1)
            {
                c->nums[i]--;
            }
            break;
        }
    }

    return c;
}

//void* multiIntoSingleMultiply(largeInt* a, largeInt* b) //b has to be number of length NodeSize
//{
//    largeInt*c = (largeInt*)malloc(sizeof(largeInt));
//    c->len = a->len+b->len;
//    long int carry=0;
//    int i=0;
//    for(i=0;i<c->len;++i)
//    {
//        c->nums[i] =
//    }
//}

//void* intal_multiply(void* intal1, void* intal2)
//{
//
//}



int main()
{
    char *a = "1";
    char *b = "9999999999999999999";

    largeInt * q = (largeInt*)intal_create(b);

    q = intal_add(intal_create(a),intal_create(b));

    //printf("%p",q);
    //printf("\n%ld",q->len);
    printf("%s",intal2str(q));
    //printf("%ld",q->len);
}
