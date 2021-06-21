#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<stdbool.h>
#include<limits.h>
#include<math.h>
#define taxi 2000



int budget=0;       //total budget
int f_budget=0;     //budget for flight
int total_hc=0;     //total hotel cost
int total_fc[12];   //total flight cost of all destination

int ssc=0;          //sight seeing cost
int nop=0;          //no. of people
int nod=0;          //no. of days
int rating=0;       //rating of hotel
int source=0;       //vertex of source will be given by user
int d=0;            //destination index

int count=0;        //used in printing
int c;              //for storing destination indexes
int dest[12];       //destinations possible are stored
int check=0;        //used in part 2 to see if hotels are available or not

int tft=0;          //total flight time
int tfc=0;          //flight cost
int tof;            //time of flight

//array to store city names
char* city[12]={"Mumbai   ","Bangalore","Goa      ","Chennai  ","Jaipur   ","Ahmedabad","Bhopal   ","Kolkata  ","Pune     ","Varanasi ","Hyderabad","Delhi    "};
char* city1[12]={"Mumbai","Bangalore","Goa","Chennai","Jaipur","Ahmedabad","Bhopal","Kolkata","Pune","Varanasi","Hyderabad","Delhi"};


void initializeflight();        //to initialize time and cost of flight
void initializehotel();         //to initialize rating,names and cost of stay in hotel
void initialize_site_seeing();  //to initialize places to visit at the destinations with price

void printflight();
void printhotel();
void print_site_seeing();

void part1();                   //to take information from user like source and destination and providing the travel budget
void part2();                   //to give suggestion to the user the destination available under his budget

//void dijkstra(int src, int ch); //algorithm for finding shortest path according to cost
void dijkstra_time(int src);    //algorithm for finding shortest path according to time
void dijkstra_cost(int src, int ch);    //algorithm for finding shortest path according to cost- used in part 1 as well as 2

int minCost(int costs[],bool sptSet[]);         //returns minimum cost path, used along with dijkstra_cost
void printPath(int parent[], int j);            //prints the route between source and destination
void printPathpart2(int parent[], int j);       //prints path for part 2
void printPath_cost(int parent[], int j);       //prints route between source and destination for minimum time, also finds corresponding flight cost
int printSolution_cost(int costs[],int Time[], int n,int parent[], int src);
int printSolutionpart2(int costs[], int n,  int parent[], int src);
int printSolution_time(int Time[], int n,int parent[], int src);
int minTime(int Time[],bool cSet[]);            //returns minimum time path, used with dijkstra_time
void description(int c);        //Descriptions of destination



//Structure made to store flight details
struct node {
    int vertex1;//source
    int vertex2;//destination
    int cost;       //cost of flight
    int time;       // time of flight in minutes
    struct node* next;
};
struct node *flight[12][12];

//Structure made to store hotel details
struct hotel{

    int vertex;
    char *hotelnames[3];        //names of hotels
    int rating[3];              //ratings of the hotels
    int cost[3];                //cost of hotel room per day
};
struct hotel *stay[12];

//Structure to store site-seeing details
struct site_seeing
{
    int vertex;
    int cost[4];            //cost of sight seeing
    char *places[4];           //name of place for sight seeing
};
struct site_seeing *site[12];



int main()
{
    initializeflight();
    initializehotel();
    initialize_site_seeing();


    int choice;//variable for switch case
    printf("\n\t\t\tMain Menu:-\n");
    printf("\n\t\t\tEnter 1.To find Route and Total budget of travel");
    printf("\n\t\t\tEnter 2.For Suggestion of nearest destination to travel");
    printf("\n\t\t\tchoose:");
    scanf("%d",&choice);
    system("cls");
    switch(choice)
    {
        case 1:
        part1();
        break;

        case 2:
        part2();
        break;

        default:
        printf("Invalid option ");

    }
    return 0;
}



void description(int c) {

    switch(c)
    {
        case 0:     //mumbai
        printf("index: %d\nMumbai, the capital of Maharashtra is a coastal city located on the west coast of India,",0);
        printf("\nand is also one the main metrolpolitan ");
        printf("cities of India.\n It is also popular as a entertainment and financial capital.");
        printf("\nMumbai is home to three UNESCO World Heritage Sites: the Elephanta Caves,");
        printf("\nChhatrapati Shivaji Maharaj Terminus, and the city's distinctive ");
        printf("ensemble of Victorian and Art Deco buildings.");
        break;

        case 1:     //bangalore
        printf("index: %d\nBangalore or Bengaluru is the capital city of Karnataka.",1);
        printf("\nBangalore is widely regarded as the Silicon Valley of India");
        printf("(or IT capital of India) because of its role as the nation's leading information technology (IT) exporter.");
        printf("\nIndian technological organisations such as ISRO, Infosys, Wipro and HAL are headquartered in the city.");
        break;

        case 2:     //goa
        printf("index: %d\nNestled between the Western Ghats and the Arabian Sea,",2);
        printf("Goa is a gorgeous, scenic place.\n It paints a perfect picture of a tropical seaside vacation spot. ");
        printf("\nGoa is famous for its happening nightlife and vibrant culture. ");
        printf("\nGoa is also known for its old churches and Portuguese-style houses, quaint by-lanes,");
        printf("breathtaking views, stunning monsoon greenery, lip-smacking cuisine, night bazaars, shopping, casinos,");
        printf("and a plethora of activities to choose from — scuba diving, kayaking, parasailing and jet skiing, among others.");
        break;

        case 3:         //chennai
        printf("index: %d\nSited on the Coromandel Coast of Bay of Bengal, Chennai is the capital city of Indian state of Tamil Nadu.",3);
        printf("\nDespite being a metropolitan city, Chennai exhibits a perfect amalgamation of art, architecture, dance, music and drama.");
        printf("\nFamous as the biggest cultural and economic centre down south, Chennai was earlier known as Madras.");
        printf("\nThe city houses several Hindu temples, churches and museums. ");
        printf("\nFrom its white-sand beaches to mouth-watering seafood, Chennai has everything for travellers.");
        break;

        case 4:     //jaipur
        printf("index: %d\nJaipur, popularly known as the Pink City of India, is the largest city in the state of Rajasthan.",4);
        printf("\nIt is also the capital of Rajasthan. ");
        printf("\nKnown for Hawa Mahal, Jal Mahal, Amer Fort, Jantar Mantar and several other places to visit,");
        printf("\nJaipur has numerous stories to tell.");
        printf("\nThe observatory, Jantar Mantar in Jaipur, is one of the World Heritage Sites.");
        printf("\nIt is a collection of architectural astronomical instruments,");
        printf("built by Sawai Jai Singh who was a Rajput king.");
        break;

        case 5:     //ahmedabad
        printf("index: %d\nAhmedabad is one of the largest city and former capital of Gujarat.",5);
        printf("\nIt is situated on the banks of Sabarmati river, mostly known for its tourist attractions.");
        printf("\nIt is famous for its cotton textiles, street food places, diamond cutting and much more. ");
        printf("\nAhmedabad has emerged as an important economic and industrial hub in India.");
        printf("\nIt is the second-largest producer of cotton in India, and its stock exchange is the country's second oldest. ");
        break;

        case 6:         //bhopal
        printf("index: %d\nIt is known as the City of Lakes for its various natural and artificial lakes,",6);
        printf("and is one of the greenest cities in India.");
        printf("\nApart from its natural beauty, Bhopal is also famous for its mosques.");
        printf("\nThe Taj-ul-Masjid in Bhopal is the largest mosque of India.");
        printf("\nBhopal is also known, sadly, for the largest industrial disaster or the Gas Tragedy, which struck it in 1984.");
        break;

        case 7:         //kolkata
        printf("index: %d\nKolkata (formerly Calcutta) is the capital of India's West Bengal state.",7);
        printf("\nFounded as an East India Company trading post, it was India's capital under the British Raj from 1773–1911.");
        printf("\nToday it’s known for its grand colonial architecture, art galleries and cultural festivals. ");
        printf("\nIt’s also home to Mother House, headquarters of the Missionaries of Charity, founded by Mother Teresa,");
        printf("whose tomb is on site.");
        break;

        case 8:         //pune
        printf("index: %d\nPune is a sprawling city in the western Indian state of Maharashtra.",8);
        printf("\nIt was once the base of the Peshwas (prime ministers) of the Maratha Empire, which lasted from 1674 to 1818.");
        printf("\nIt's known for the grand Aga Khan Palace, built in 1892 and now a memorial to Mahatma Gandhi,");
        printf("whose ashes are preserved in the garden. ");
        printf("\nThe 8th-century Pataleshwar Cave Temple is dedicated to the Hindu god Shiva.");
        break;

        case 9:         //varanasi
        printf("index: %d\nVaranasi is a city in the northern Indian state of Uttar Pradesh dating to the 11th century B.C.",9);
        printf("\nRegarded as the spiritual capital of India, the city draws Hindu pilgrims who bathe in the Ganges River’s ");
        printf("sacred waters and perform funeral rites");
        printf("\nAlong the city's winding streets are some 2,000 temples, including Kashi Vishwanath, the Golden Temple  ");
        printf("dedicated to the Hindu god Shiva. ");
        break;

        case 10:        //hyderabad
        printf("index: %d\nHyderabad is the capital of southern India's Telangana state.",10);
        printf("\nA major center for the technology industry, it's home to many upscale restaurants and shops.");
        printf("\nIts historic sites include Golconda Fort, a former diamond-trading center that was once the ");
        printf("Qutb Shahi dynastic capital. ");
        printf("\nThe Charminar, a 16th-century mosque whose 4 arches support towering minarets,");
        printf("is an old city landmark near the long-standing Laad Bazaar.");
        break;

        case 11:        //delhi
        printf("index: %d\nDelhi, India’s capital territory, is a massive metropolitan area in the country’s north.",11);
        printf("\nIn Old Delhi, a neighborhood dating to the 1600s, stands the imposing Mughal-era Red Fort,");
        printf("\n a symbol of India, and the sprawling Jama Masjid mosque, whose courtyard accommodates 25,000 people. ");
        printf("Nearby is Chandni Chowk, a vibrant bazaar filled with food carts, sweets shops and spice stalls.");
        break;
    }






}




void printPath(int parent[], int j)         //for printing the route
{

    // Base Case : If j is source
    if (parent[j] == - 1)
        return;

    printPath(parent, parent[j]);
    tfc+=flight[j][parent[j]]->cost;

    if(parent[parent[parent[j]]]!=-1)
    printf("%s--> ", city1[j]);
    else
        printf("%s ",city1[j]);

}


void printPath_cost(int parent[], int j)         //for time
{

    // Base Case : If j is source
    if (parent[j] == - 1)
        return;

    printPath_cost(parent, parent[j]);

    if(parent[parent[parent[j]]]!=-1)
    printf("%s--> ", city1[j]);
    else
        printf("%s ",city1[j]);

}



int minTime(int Time[],bool cSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < 12; v++)
        if (cSet[v] == false && Time[v] <= min)         //check if value of time is less then the current minimum, then replace
            min = Time[v],
            min_index = v;

    return min_index;
}



int printSolution_time(int Time[], int n,int parent[], int src)         //for time
{

        printf("\n\t\t\tRequired:%s -> %s \n\n\t\t\tOne way time: %d mins\t\tRoute: %s-->",city1[src],city1[d],Time[d],city1[src]);

        tft=2*Time[d];             //total flight cost

        printPath(parent, d);
}




void dijkstra_time(int src)
{


    int Time[12];           // This array stores time between source and destination
                            //Time[i] stores shortest time between source and i


    bool cSet[12];         // cSet[i] will true if vertex i is included in shortest time from src to i is finalized


    int parent[12];         // Parent array to store shortest path

    // Initialize all time as
    // INFINITE and cSet[] as false
    for (int i = 0; i < 12; i++)
    {
        parent[src] = -1;
        Time[i] = INT_MAX;
        cSet[i] = false;
    }

    // time of source vertex
    // from itself is always 0
    Time[src] = 0;


    for (int count = 0; count < 12; count++)
    {

        int u = minTime(Time, cSet);        //if vertex isn't processed yet, then we send it to the function
                                            //and it will return the minimum time of index

        cSet[u] = true;     // Mark the picked vertex as processed


        for (int v = 0; v < 12; v++)

            // Update time[v] only if is
            // not in cSet, there is
            // an edge from u to v, and
            // total time of path from
            // src to v through u is smaller
            // than current value of
            // cost[v]

            if (!cSet[v] && flight[u][v]->time!=0 &&Time[u] + flight[u][v]->time  < Time[v])
            {
                //update the time and parent in the case that the new time is lesser then previous one
                parent[v] = u;
                Time[v] = Time[u] + flight[u][v]->time;
            }
    }

    //for printing
    printSolution_time(Time, 12, parent,src);
}





int minCost(int costs[],bool cSet[])
{

    // Initialize min value
    int min = INT_MAX;
    int min_index;

    for (int v = 0; v < 12; v++)
        if (cSet[v] == false && costs[v] <= min)            //set minimum cost and return minimum index
        {
             min = costs[v];
            min_index = v;

        }

    return min_index;
}



void printPathpart2(int parent[], int j)
{
    count++;
    // Base Case : If j is source
    if (parent[j] == - 1)
        return;

    printPath(parent, parent[j]);

    if(count==0)
    printf("%s--> ", city1[j]);
    else
        printf("%s",city1[j]);


}


int printSolutionpart2(int costs[], int n,  int parent[], int src)
{

    for(int x1=0;x1<12;x1++)
    {
        dest[x1]=-1;
    }

    printf("\n\nSuggested Destination\t\t Total Flight Cost \t\tPath");
    for (int i = 0; i < 12; i++)
    {


        if(nop*2*costs[i]<f_budget && src!=i)           // if the cost for that destination lies within the budget for flight.
                                                    //then store it in array dest
        {
            dest[c]=i;
            c++;
            total_fc[i]=nop*2*costs[i];
           printf("\n %s \t\t    %d\t\t    %s --> ",city[i], nop*2*costs[i], city1[src]);
            printPathpart2(parent, i);
            printf("\n");
        }

    }
}


int printSolution_cost(int costs[],int Time[], int n,int parent[], int src)
{
        printf("\n\t\t\tRequired : %s to %s \n\n\t\t\tOne way flight cost per person: %d rupees\t\tRoute: %s--> ",city1[src],city1[d],costs[d],city1[src]);
        tfc=nop*2*costs[d];             //total flight cost
        tft=2*Time[d];                  //total flight time
        printPath_cost(parent, d);
}




void dijkstra_cost(int src, int ch)
{
    int rem_budget;         //budget remaining after flight, used for part 2

    // array costs[i] will hold the shortest distance from src to i
    int costs[12];

    int Time[12];           //for storing time corresponding to the cost


    // cSet[i] will true if vertex i is included in shortest distance from src to i is finalized
    bool cSet[12];


    // Parent array to store shortest path
    int parent[12];

    // Initialize all distances as INFINITE and cSet[] as false
    for (int i = 0; i < 12; i++)
    {
        parent[src] = -1;
        costs[i] = INT_MAX;
        Time[i] = INT_MAX;
        cSet[i] = false;
    }

    // cost and time of source vertex from itself is always 0
    costs[src] = 0;
    Time[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < 12; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not yet visited.
        //u is always equal to src in first iteration.
        int u = minCost(costs, cSet);

        // Mark the picked vertex
        // as visited
        cSet[u] = true;

        // Update cost and time value of the
        // adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < 12; v++)

            // Update costs[v] only if is
            // not in cSet, there is
            // an edge from u to v, and
            // total cost of path from
            // src to v through u is smaller
            // than current value of
            // cost[v]
            if (!cSet[v] && flight[u][v]->cost!=0 && costs[u] + flight[u][v]->cost  < costs[v])
            {
                parent[v] = u;
                costs[v] = costs[u] + flight[u][v]->cost;
                Time[v] = Time[u] + flight[u][v]->time;
            }
    }


    if(ch==1)           //print for path 1
    printSolution_cost(costs,Time, 12, parent,src);
    else            //print for path 2
    printSolutionpart2(costs,12,parent,src);


    if(ch==2)           //finding hotels for part 2
    {
        int des;

        printf("\n\n\nSuggested destinations for you are:   \n");
        for(int j1=0;j1<c;j1++)
        {
            printf("\n\n\n%s  \t",city1[dest[j1]]);
            description(dest[j1]);
            printf("\n\t\t\tSite seeing places:  \n");
            printf("\n\t\t\tSerial NO.\tPlaces\n");
            for(int j=0;j<4;j++)
            {
                printf("\t\t\t%d\t",j+1);
                printf("%s\t\t\t\n",site[dest[j1]]->places[j]);


            }


        }

        printf("\n\t\t\tWhich destination would you like to visit?   \n");

        printf("\n\t\t\tEnter the index number: ");

        scanf("%d",&des);
        rem_budget=budget-nop*2*costs[des];
        printf("\n\t\t\tremaining budget:  %d",rem_budget);

         printf("\n\t\t\tThe Hotels according to your destination are:\n");

         double s1=(double) nop/4;              //each room has a capacity for four people
        int nopp=ceil(s1);


        for(int j=0;j<3;j++) {

            if(nopp*nod*(stay[des]->cost[j]) <=rem_budget)      //finding all hotels under remaining budget
            {
                check=1;
                printf("\t\t\t%d\t",j+1);
                printf("hotel:  %s\t",stay[des]->hotelnames[j]);
                printf("price:  %d\t",stay[des]->cost[j]);
                printf("rating: %d stars\n",stay[des]->rating[j]);
            }

        }

        if(check==0)                //if no hotels are available under remining budget print so
        {
            printf("\n\t\t\tSorry but there seems to be no hotels available for the budget you entered\n");
        }


        printf("\n\t\t\tEnter the rating of a hotel for stay ");
        scanf("%d",&rating);

        int costindex=0;            //find array element corresponding to hotel rating
        if(rating==5)
        costindex=0;
        else if(rating==4)
        costindex=1;
        else
        costindex=2;


        total_hc=stay[des]->cost[costindex]*nod*nopp;           //hotel cost
        system("cls");
        if(total_hc>rem_budget)
            printf("\n\t\t\tSorry but there seems to be no hotels available for the budget you entered\n");
        printf("\n\n\n\t\t\tDestination: %s",city1[des]);
        printf("\n\n\t\t\tTotal cost of flight is:  %d \n",total_fc[des]);
        if(total_hc<=rem_budget)
            printf("\n\t\t\tTotal cost of hotel stay is:  %d \n",total_hc);

        if(rem_budget-total_hc>0)
            printf("\nYou still have %d  rupees remaining. Feel free to use them to your leisure. Enjoy your stay!\n\n",rem_budget-total_hc);


        }

}







void part1()
{
    int s=0;//for getting index of the destination& source

    char source[10],destination[10];
    printf("\n\n");

    //To take source and destination from the user
    printf("\n\t\t\tEnter the source: ");
    scanf("%s",source);
    printf("\n\t\t\tEnter the destination: ");
    scanf("%s",destination);
    printf("\n\n\t\t\tSource is %s and destination is %s\n",source,destination);

    //To find the index of source and destination entered by the user
    for(int i=0;i<12;i++)
    {
        if(strcmp(city1[i],destination)==0)
            d=i;
    }

    for(int i=0;i<12;i++)
    {
        if(strcmp(city1[i],source)==0)
            s=i;
    }

    //To get the details of number of people and number of days of travel
    printf("\n\n\t\t\tEnter the number of people travelling: ");
    scanf("%d",&nop);
    printf("\n\t\t\tEnter the number of days for travelling ");
    scanf("%d",&nod);
    printf("\n\t\t\tThe Hotels according to your destination are:\n");

    //To display the hotels available according to the destination
    for(int j=0;j<3;j++) {
        printf("\t\t\t%d\t",j+1);
        printf("hotel:  %s\t",stay[d]->hotelnames[j]);
        printf("price:  %d\t",stay[d]->cost[j]);
        printf("rating: %d stars\n",stay[d]->rating[j]);
    }

    printf("\n\t\t\tAll hotels have one room having max. accomodation for 4 people.\n");


    double s1=(double) nop/4;
    int nopp=ceil(s1);



    printf("\n\t\t\tEnter the rating of a hotel for stay ");
    scanf("%d",&rating);

    //To display the places for site seeing the user can visit according to the destination
    printf("\n\n\t\t\tThe places to visit according to your destination are:\n");
    printf("\n\t\t\tNO.\tPlaces\t\t\t\tCost_per_ticket\n");
    for(int j=0;j<4;j++)
    {
        printf("\t\t\t%d\t",j+1);
        printf("%s\t",site[d]->places[j]);
        printf("%d\t\n",site[d]->cost[j]);

    }

    int option;

    //for user to choose the places he/she wants to visit for site seeing
    printf("\n\t\t\tEnter the number of places to visit: ");
    scanf("%d",&option);

    int option_no[option];
    int x;

    for(int i=0;i<option;i++)
    {
        printf("\n\t\t\tEnter the option number ");
        scanf("%d",&x);
        option_no[i]=x-1;

    }

            printf("\n\t\t\tOptions chosen are :   ");

    for(int i1=0;i1<option;i1++)
    {
        x=option_no[i1]+1;
        printf("%d\t",x);
    }

    int costindex=0;            //find array element corresponding to hotel rating
    if(rating==5)
        costindex=0;
    else if(rating==4)
        costindex=1;
    else
        costindex=2;

    int temp=stay[d]->cost[costindex];          //cost per day per room of chosen hotel

    total_hc=nopp*nod*temp;
    system("cls");
    int check1;
    //To decide whether the user prefers the flight with minimum cost or minimum time
    printf("\n\t\t\tDo you want us to suggest path with minimum time or minimum cost ?\n\n\t\t\tEnter 1.for minimum cost 2.for min time: ");
    scanf("%d",&check1);

    if(check1==1)
    {
    //for minimum cost
        printf("hi");
        system("cls");
        printf("\n\n");
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        printf("\t\t\tPlan for minimum cost :\n");
        printf("\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    //function used to find the route ,cost,time
    //route according to minimum cost required in which route
        dijkstra_cost(s,1);  //for flight, path, time
        printf("\n\t\t\tTotal flight Time:\t%d mins",tft);
        printf("\n\n\t\t\tTravel & Accomodation charges:\t\tPrice(In rupees)\n");

        printf("\n\t\t\tTotal flight cost:\t                     %d",tfc);
        printf("\n\t\t\tTotal hotel cost:\t                     %d",total_hc);

        for(int j1=0;j1<option;j1++)            //for sight seeing cost
        {
            int x=site[d]->cost[option_no[j1]];
            ssc=ssc+x;
        }
        ssc=ssc*nop;
        printf("\n\t\t\tTotal site-seeing cost: \t              %d",ssc);

        printf("\n\t\t\tTaxi cost(standard 2000/day) :\t             %d",2000*nod);
        budget=tfc+nod*2000+total_hc+ssc;      //flight plus taxi plus hotel plus sight seeing

        printf("\n\t\t\t-------------------------------------------------------");
        //The total budget required by the user for the entire travel
        printf("\n\t\t\tTotal budget:\t                            %d\n",budget);
        //The discount offered by the agency
        printf("\n\n\t\t\tPress 1 if you are a student, 2 if you are travelling in a family of 4, and 0 otherwise :");
        int disc;
        scanf("%d",&disc);
        if(disc==1)                 //discount for student
        {
                   printf("\n\t\t\tCongratulations!!! you can avail 10 percent discount.\n");
                   printf("\t\t\tYour discounted budget is:  %f \n",budget-(budget*0.1));
        }
        if(disc==2)                 //discount for family
        {
             printf("\n\t\t\tCongratulations!!! you can avail 5 percent discount.\n");
                   printf("\t\t\tYour discounted budget is:  %f \n",budget-(budget*0.05));
        }

        printf("------------------------------------------------------------------------------------------------------------------------");
        printf("\n\n\n");

    }

    else if(check1==2)
    {
        //for minimum time
        system("cls");
        printf("\n\n");
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        printf("\t\t\tPlan for minimum time :\n");

        printf("\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        //function used to find the route ,cost,time
    //route according to minimum time required in which route
        dijkstra_time(s);  //for flight, path, time
        printf("\n\t\t\tTotal flight time is : %d mins ",tft);
        printf("\n\n\t\t\tTravel & Accomodation charges:\t\tPrice(In rupees)\n");
        printf("\n\t\t\tTotal flight cost:\t                     %d",tfc*nop*2);
        printf("\n\t\t\tTotal hotel cost:\t                     %d",total_hc);

        for(int j1=0;j1<option;j1++)            //sight seeing cost
        {
            int x=site[d]->cost[option_no[j1]];
            ssc=ssc+x;
        }
        ssc=ssc*nop;
        printf("\n\t\t\tTotal site-seeing cost: \t              %d",ssc);

        printf("\n\t\t\tTaxi cost(standard 2000/day) :\t             %d",2000*nod);
        budget=tfc*2*nop+nod*2000+total_hc+ssc;      //flight plus taxi plus hotel plus sight seeing

        printf("\n\t\t\t-------------------------------------------------------");
        printf("\n\t\t\tTotal budget:\t                            %d\n",budget);
        //The discount offered by the agency
        printf("\n\n\t\t\tPress 1 if you are a student, 2 if you are travelling in a family of 4, and 0 otherwise :");
        int disc;
        scanf("%d",&disc);
        if(disc==1)                 //discount for student
        {
                   printf("\n\t\t\tCongratulations!!! you can avail 10 percent discount.\n");
                   printf("\t\t\tYour discounted budget is:  %f \n",budget-(budget*0.1));
        }
        if(disc==2)                 //discount for family
        {
             printf("\n\t\t\tCongratulations!!! you can avail 5 percent discount.\n");
                   printf("\t\t\tYour discounted budget is:  %f \n",budget-(budget*0.05));
        }

        printf("------------------------------------------------------------------------------------------------------------------------");
        printf("\n\n\n");



    }


}



void part2()
{
    int s=0;//for getting index of the destination& source

    char source[10];
    //The source,number of people, number of days and budget is taken by the user for suggesting the destination
    printf("\n\n");
    printf("\n\t\t\tEnter the source: ");
    scanf("%s",source);

     for(int i=0;i<12;i++)
    {
        if(strcmp(city1[i],source)==0)
            s=i;
    }


    printf("\n\n\t\t\tEnter the number of people travelling: ");
    scanf("%d",&nop);
    printf("\n\t\t\tEnter the number of days for travelling ");
    scanf("%d",&nod);
    printf("\n\t\t\tEnter total budget :  ");
    scanf("%d",&budget);
    printf("\n\t\t\tEnter budget for flight:  ");
    printf("\n\t\t\tWe suggest a minimum 6000 rupees per person so that we can suggest you good places!\n");
    printf("\t\t\t");
    scanf("%d",&f_budget);

    dijkstra_cost(s,2);

}




void initializeflight()
{

    //Allocating if there is a flight of one city to another


    int i,j;
    //Allocating the space;
    for(i=0;i<12;i++) {
        for(j=0;j<12;j++)
        {
            flight[i][j]=(struct node*)malloc(sizeof(struct node));
        }

    }


       flight[0][0]->time=0;
    flight[1][1]->time=0;
    flight[2][2]->time=0;
    flight[3][3]->time=0;
    flight[4][4]->time=0;
    flight[5][5]->time=0;
    flight[6][6]->time=0;
    flight[7][7]->time=0;
    flight[8][8]->time=0;
    flight[9][9]->time=0;
    flight[10][10]->time=0;
    flight[11][11]->time=0;


    flight[0][1]->time=flight[1][0]->time=90;
    flight[0][2]->time=flight[2][0]->time=80;
    flight[0][3]->time=flight[3][0]->time=120;
    flight[0][4]->time=flight[4][0]->time=100;
    flight[0][5]->time=flight[5][0]->time=80;
    flight[0][6]->time=flight[6][0]->time=90;
    flight[0][7]->time=flight[7][0]->time=165;
    flight[0][8]->time=flight[8][0]->time=0;
    flight[0][9]->time=flight[9][0]->time=0;
    flight[0][10]->time=flight[10][0]->time=130;
    flight[0][11]->time=flight[11][0]->time=130;

    flight[1][2]->time=flight[2][1]->time=80;
    flight[1][3]->time=flight[3][1]->time=75;
    flight[1][4]->time=flight[4][1]->time=235;
    flight[1][5]->time=flight[5][1]->time=110;
    flight[1][6]->time=flight[6][1]->time=125;
    flight[1][7]->time=flight[7][1]->time=145;
    flight[1][8]->time=flight[8][1]->time=90;
    flight[1][9]->time=flight[9][1]->time=140;
    flight[1][10]->time=flight[10][1]->time=80;
    flight[1][11]->time=flight[11][1]->time=160;

    flight[2][3]->time=flight[3][2]->time=105;
    flight[2][4]->time=flight[4][2]->time=0;
    flight[2][5]->time=flight[5][2]->time=150;
    flight[2][6]->time=flight[6][2]->time=0;
    flight[2][7]->time=flight[7][2]->time=0;
    flight[2][8]->time=flight[8][2]->time=55;
    flight[2][9]->time=flight[9][2]->time=0;
    flight[2][10]->time=flight[10][2]->time=70;
    flight[2][11]->time=flight[11][2]->time=0;

    flight[3][4]->time=flight[4][3]->time=0;
    flight[3][5]->time=flight[5][3]->time=130;
    flight[3][6]->time=flight[6][3]->time=0;
    flight[3][7]->time=flight[7][3]->time=140;
    flight[3][8]->time=flight[8][3]->time=120;
    flight[3][9]->time=flight[9][3]->time=155;
    flight[3][10]->time=flight[10][3]->time=70;
    flight[3][11]->time=flight[11][3]->time=180;

    flight[4][5]->time=flight[5][4]->time=105;
    flight[4][6]->time=flight[6][4]->time=0;
    flight[4][7]->time=flight[7][4]->time=135;
    flight[4][8]->time=flight[8][4]->time=135;
    flight[4][9]->time=flight[9][4]->time=110;
    flight[4][10]->time=flight[10][4]->time=120;
    flight[4][11]->time=flight[11][4]->time=60;

    flight[5][6]->time=flight[6][5]->time=0;
    flight[5][7]->time=flight[7][5]->time=165;
    flight[5][8]->time=flight[8][5]->time=90;
    flight[5][9]->time=flight[9][5]->time=110;
    flight[5][10]->time=flight[10][5]->time=100;
    flight[5][11]->time=flight[11][5]->time=80;

    flight[6][7]->time=flight[7][6]->time=0;
    flight[6][8]->time=flight[8][6]->time=0;
   flight[6][9]->time=flight[9][6]->time=0;
    flight[6][10]->time=flight[10][6]->time=145;
    flight[6][11]->time=flight[11][6]->time=90;

    flight[7][8]->time=flight[8][7]->time=0;
    flight[7][9]->time=flight[9][7]->time=80;
    flight[7][10]->time=flight[10][7]->time=125;
    flight[7][11]->time=flight[11][7]->time=130;

    flight[8][9]->time=flight[9][8]->time=0;
    flight[8][10]->time=flight[10][8]->time=80;
    flight[8][11]->time=flight[11][8]->time=120;

    flight[9][10]->time=flight[10][9]->time=135;
    flight[9][11]->time=flight[11][9]->time=60;

    flight[10][11]->time=flight[11][10]->time=135;

       flight[0][0]->cost=0;
    flight[1][1]->cost=0;
    flight[2][2]->cost=0;
    flight[3][3]->cost=0;
    flight[4][4]->cost=0;
    flight[5][5]->cost=0;
    flight[6][6]->cost=0;
    flight[7][7]->cost=0;
    flight[8][8]->cost=0;
    flight[9][9]->cost=0;
    flight[10][10]->cost=0;
    flight[11][11]->cost=0;

    flight[0][1]->cost=flight[1][0]->cost=2400;
    flight[0][2]->cost=flight[2][0]->cost=2150;
    flight[0][3]->cost=flight[3][0]->cost=1960;
    flight[0][4]->cost=flight[4][0]->cost=2410;
    flight[0][5]->cost=flight[5][0]->cost=2010;
    flight[0][6]->cost=flight[6][0]->cost=2450;
    flight[0][7]->cost=flight[7][0]->cost=3555;
    flight[0][8]->cost=flight[8][0]->cost=0;
    flight[0][9]->cost=flight[9][0]->cost=0;
    flight[0][10]->cost=flight[10][0]->cost=2150;
    flight[0][11]->cost=flight[11][0]->cost=3000;

    flight[1][2]->cost=flight[2][1]->cost=1800;
    flight[1][3]->cost=flight[3][1]->cost=1650;
    flight[1][4]->cost=flight[4][1]->cost=3250;
    flight[1][5]->cost=flight[5][1]->cost=3040;
    flight[1][6]->cost=flight[6][1]->cost=3662;
    flight[1][7]->cost=flight[7][1]->cost=3010;
    flight[1][8]->cost=flight[8][1]->cost=2198;
    flight[1][9]->cost=flight[9][1]->cost=6182;
    flight[1][10]->cost=flight[10][1]->cost=1900;
    flight[1][11]->cost=flight[11][1]->cost=3400;

    flight[2][3]->cost=flight[3][2]->cost=2720;
    flight[2][4]->cost=flight[4][2]->cost=0;
    flight[2][5]->cost=flight[5][2]->cost=2400;
    flight[2][6]->cost=flight[6][2]->cost=0;
    flight[2][7]->cost=flight[7][2]->cost=0;
    flight[2][8]->cost=flight[8][2]->cost=4800;
    flight[2][9]->cost=flight[9][2]->cost=0;
    flight[2][10]->cost=flight[10][2]->cost=2050;
    flight[2][11]->cost=flight[11][2]->cost=0;

    flight[3][4]->cost=flight[4][3]->cost=0;
    flight[3][5]->cost=flight[5][3]->cost=2725;
    flight[3][6]->cost=flight[6][3]->cost=0;
    flight[3][7]->cost=flight[7][3]->cost=2922;
    flight[3][8]->cost=flight[8][3]->cost=3164;
    flight[3][9]->cost=flight[9][3]->cost=4838;
    flight[3][10]->cost=flight[10][3]->cost=1512;
    flight[3][11]->cost=flight[11][3]->cost=2580;

    flight[4][5]->cost=flight[5][4]->cost=2162;
    flight[4][6]->cost=flight[6][4]->cost=0;
    flight[4][7]->cost=flight[7][4]->cost=3370;
    flight[4][8]->cost=flight[8][4]->cost=3435;
    flight[4][9]->cost=flight[9][4]->cost=5354;
    flight[4][10]->cost=flight[10][4]->cost=2897;
    flight[4][11]->cost=flight[11][4]->cost=1830;

    flight[5][6]->cost=flight[6][5]->cost=0;
    flight[5][7]->cost=flight[7][5]->cost=3867;
    flight[5][8]->cost=flight[8][5]->cost=1917;
    flight[5][9]->cost=flight[9][5]->cost=5046;
    flight[5][10]->cost=flight[10][5]->cost=2180;
    flight[5][11]->cost=flight[11][5]->cost=1950;

    flight[6][7]->cost=flight[7][6]->cost=0;
    flight[6][8]->cost=flight[8][6]->cost=0;
    flight[6][9]->cost=flight[9][6]->cost=0;
    flight[6][10]->cost=flight[10][6]->cost=3195;
    flight[6][11]->cost=flight[11][6]->cost=2166;

    flight[7][8]->cost=flight[8][7]->cost=0;
    flight[7][9]->cost=flight[9][7]->cost=3187;
    flight[7][10]->cost=flight[10][7]->cost=2780;
    flight[7][11]->cost=flight[11][7]->cost=3298;

    flight[8][9]->cost=flight[9][8]->cost=0;
    flight[8][10]->cost=flight[10][8]->cost=2500;
    flight[8][11]->cost=flight[11][8]->cost=2511;

    flight[9][10]->cost=flight[10][9]->cost=3503;
    flight[9][11]->cost=flight[11][9]->cost=1455;

    flight[10][11]->cost=flight[11][10]->cost=2890;



    for(int i1=0;i1<12;i1++)
    {
        for(int j1=0;j1<12;j1++)
        {
            flight[i1][j1]->vertex1=i1;
            flight[i1][j1]->vertex2=j1;
        }
    }


}





void initializehotel()
{
    for(int x=0;x<12;x++)
    {
        stay[x]=malloc(sizeof(struct hotel));
        stay[x]->vertex=x;
        stay[x]->rating[0]=5;
        stay[x]->rating[1]=4;
        stay[x]->rating[2]=3;

    }

    //Hotel Names

    //mumbai

    stay[0]->hotelnames[0]="The Lalit       ";


    stay[0]->hotelnames[1]="Radisson Resorts";
    stay[0]->hotelnames[2]="IBIS Hotels     ";

    //bangalore
    stay[1]->hotelnames[0]="Oberoi Hotels   ";
    stay[1]->hotelnames[1]="IRIS Hotel      ";
    stay[1]->hotelnames[2]="Orchard Suites  ";

    //goa
    stay[2]->hotelnames[0]="Novotel Resorts ";
    stay[2]->hotelnames[1]="Flora Grand     ";
    stay[2]->hotelnames[2]="Golden Plateau  ";

    //chennai
    stay[3]->hotelnames[0]="ITC Grand       ";
    stay[3]->hotelnames[1]="Green Park      ";
    stay[3]->hotelnames[2]="Woodland Resorts";

    //jaipur
    stay[4]->hotelnames[0]="ITC Rajputana   ";
    stay[4]->hotelnames[1]="Umaid Mahal     ";
    stay[4]->hotelnames[2]="Arya Niwas      ";

    //ahmedabad
    stay[5]->hotelnames[0]="Hyatt Regency   ";
    stay[5]->hotelnames[1]="Fortune Park    ";
    stay[5]->hotelnames[2]="Ginger Hotels   ";

    //bhopal
    stay[6]->hotelnames[0]="Jehan Numa Palace";
    stay[6]->hotelnames[1]="Noor-us-Subah    ";
    stay[6]->hotelnames[2]="Graces Resort    ";

    //kolkata
    stay[7]->hotelnames[0]="The Westin       ";
    stay[7]->hotelnames[1]="Holiday Inn      ";
    stay[7]->hotelnames[2]="Fern Residency   ";

    //pune
    stay[8]->hotelnames[0]="Hotel Sayaji      ";
    stay[8]->hotelnames[1]="Lemon Tree Resorts";
    stay[8]->hotelnames[2]="Royal Orchard     ";


    //varanasi
    stay[9]->hotelnames[0]="Taj Ganges       ";
    stay[9]->hotelnames[1]="Grapevine Hotel  ";
    stay[9]->hotelnames[2]="Rivera Hotel     ";

    //hyderabad
    stay[10]->hotelnames[0]="Novotel          ";
    stay[10]->hotelnames[1]="Oakwood Resorts  ";
    stay[10]->hotelnames[2]="Lemon Tree       ";

    //delhi
    stay[11]->hotelnames[0]="J W Marriot      ";
    stay[11]->hotelnames[1]="Holiday Inn      ";
    stay[11]->hotelnames[2]="IBIS Hotel       ";


    //hotel prices

    //mumbai
    stay[0]->cost[0]=6700;
    stay[0]->cost[1]=5000;
    stay[0]->cost[2]=3300;

    //bangalore
    stay[1]->cost[0]=6100;
    stay[1]->cost[1]=2900;
    stay[1]->cost[2]=1900;

    //goa
    stay[2]->cost[0]=7600;
    stay[2]->cost[1]=3300;
    stay[2]->cost[2]=2150;

    //chennai
    stay[3]->cost[0]=5600;
    stay[3]->cost[1]=3800;
    stay[3]->cost[2]=2400;

    //jaipur
    stay[4]->cost[0]=7500;
    stay[4]->cost[1]=2550;
    stay[4]->cost[2]=1215;

    //ahmedabad
    stay[5]->cost[0]=4760;
    stay[5]->cost[1]=3250;
    stay[5]->cost[2]=2460;

    //bhopal
    stay[6]->cost[0]=6700;
    stay[6]->cost[1]=5000;
    stay[6]->cost[2]=3300;

    //kolkata
    stay[7]->cost[0]=7960;
    stay[7]->cost[1]=3130;
    stay[7]->cost[2]=2500;

    //pune
    stay[8]->cost[0]=4200;
    stay[8]->cost[1]=2300;
    stay[8]->cost[2]=1620;

    //varanasi
    stay[9]->cost[0]=6350;
    stay[9]->cost[1]=3580;
    stay[9]->cost[2]=2050;

    //hyderabad
    stay[10]->cost[0]=5200;
    stay[10]->cost[1]=3600;
    stay[10]->cost[2]=2690;

    //delhi
    stay[11]->cost[0]=6850;
    stay[11]->cost[1]=4130;
    stay[11]->cost[2]=2110;
}


void initialize_site_seeing()
{
    for(int i=0;i<12;i++)
    {
        site[i]=malloc(sizeof(struct site_seeing));
        site[i]->vertex=i;
    }
    //mumbai
    site[0]->places[0]="Gateway of India        \t";
    site[0]->places[1]="Elephanta Caves         \t";
    site[0]->places[2]="Marine Drive            \t";
    site[0]->places[3]="Film City               \t";

    //bangalore
    site[1]->places[0]="Bangalore Palace        \t";
    site[1]->places[1]="Cubbon Park             \t";
    site[1]->places[2]="Ulsoor Lake             \t";
    site[1]->places[3]="Chunchi Falls           \t";

    //goa
    site[2]->places[0]="Dona Paula              \t";
    site[2]->places[1]="Fort Agauda             \t";
    site[2]->places[2]="Dudhsagar Falls         \t";
    site[2]->places[3]="Chapora Fort            \t";

    //chennai
    site[3]->places[0]="Arignar Anna zoo        \t";
    site[3]->places[1]="Ashtalakshmi Temple     \t";
    site[3]->places[2]="Kolli Hills             \t";
    site[3]->places[3]="Breezy Beach            \t";

    //jaipur
    site[4]->places[0]="Amer Fort               \t";
    site[4]->places[1]="City Palace             \t";
    site[4]->places[2]="Hawa Mahal              \t";
    site[4]->places[3]="Jantar Mantar           \t";

    //ahmedabad
    site[5]->places[0]="Sabarmati Ashram        \t";
    site[5]->places[1]="Kankaria Lake           \t";
    site[5]->places[2]="Dada Hari Wav           \t";
    site[5]->places[3]="Swaminarayan Temple     \t";

    //bhopal
    site[6]->places[0]="Upper Lake               \t";
    site[6]->places[1]="Bhimbetka Rock Shelters  \t";
    site[6]->places[2]="Shaukat Mahal            \t";
    site[6]->places[3]="Van Vihar                \t";

    //kolkata
    site[7]->places[0]="Victoria Memorial        \t";
    site[7]->places[1]="Fort William             \t";
    site[7]->places[2]="Howrah Bridge            \t";
    site[7]->places[3]="Belur Math               \t";

    //pune
    site[8]->places[0]="Shaniwar Wada            \t";
    site[8]->places[1]="Dagdusheth Halwai Temple \t";
    site[8]->places[2]="Lal Mahal                \t";
    site[8]->places[3]="Sinhagad Fort            \t";

    //varanasi
    site[9]->places[0]="Dashashwamedh Ghat       \t";
    site[9]->places[1]="Manikarnika Ghat         \t";
    site[9]->places[2]="Dhamekh Stupa            \t";
    site[9]->places[3]="Assi Ghat                \t";

    //hyderabad
    site[10]->places[0]="Golconda Fort           \t";
    site[10]->places[1]="Charminar               \t";
    site[10]->places[2]="Hussain Sagar Lake      \t";
    site[10]->places[3]="Vhowmahalla Palace      \t";

    //delhi
    site[11]->places[0]="India Gate              \t";
    site[11]->places[1]="Red Fort                \t";
    site[11]->places[2]="Qutab Minar             \t";
    site[11]->places[3]="Humayu's Tomb           \t";


    site[0]->cost[0]=100;
    site[0]->cost[1]=70;
    site[0]->cost[2]=50;
    site[0]->cost[3]=100;

    site[1]->cost[0]=60;
    site[1]->cost[1]=30;
    site[1]->cost[2]=40;
    site[1]->cost[3]=50;

    site[2]->cost[0]=30;
    site[2]->cost[1]=40;
    site[2]->cost[2]=50;
    site[2]->cost[3]=35;

    site[3]->cost[0]=35;
    site[3]->cost[1]=50;
    site[3]->cost[2]=40;
    site[3]->cost[3]=45;

    site[4]->cost[0]=40;
    site[4]->cost[1]=35;
    site[4]->cost[2]=60;
    site[4]->cost[3]=90;

    site[5]->cost[0]=70;
    site[5]->cost[1]=30;
    site[5]->cost[2]=40;
    site[5]->cost[3]=55;

    site[6]->cost[0]=50;
    site[6]->cost[1]=30;
    site[6]->cost[2]=40;
    site[6]->cost[3]=35;

    site[7]->cost[0]=40;
    site[7]->cost[1]=35;
    site[7]->cost[2]=60;
    site[7]->cost[3]=35;

    site[8]->cost[0]=45;
    site[8]->cost[1]=60;
    site[8]->cost[2]=40;
    site[8]->cost[3]=50;

    site[9]->cost[0]=40;
    site[9]->cost[1]=35;
    site[9]->cost[2]=35;
    site[9]->cost[3]=45;

    site[10]->cost[0]=50;
    site[10]->cost[1]=60;
    site[10]->cost[2]=55;
    site[10]->cost[3]=45;

    site[11]->cost[0]=80;
    site[11]->cost[1]=75;
    site[11]->cost[2]=85;
    site[11]->cost[3]=40;

}

//For printing all flight available
void printflight()
{
    for(int i=0;i<12;i++)
    {
        for(int j=0;j<12;j++)
        {
            if(flight[i][j]->cost!=0)
            {
                printf("source : %s\t",city[i]);
                printf("destination : %s\t\t",city[j] );
               printf("Flight time : %d  mins\t\t",flight[i][j]->time);
               printf("Flight cost:  %d rs\n",flight[i][j]->cost);


            }

        }
    }
}

//for printing all hotel available
void printhotel()
{
    for(int i=0;i<12;i++)
    {
        printf("%s\n",city[i]);
        for(int j=0;j<3;j++)
        {
            printf("hotel:  %s\t",stay[i]->hotelnames[j]);
            printf("price:  %d\t",stay[i]->cost[j]);
            printf("rating: %d stars\n",stay[i]->rating[j]);
        }
        printf("\n");
    }
}

//for printing all site seeing places
void print_site_seeing()
{
    for(int i=0;i<12;i++)
    {
        printf("%s\n",city[i]);
        for(int j=0;j<4;j++)
        {
            printf("Place:  %s\t",site[i]->places[j]);
            printf("Cost:  %d\t\n",site[i]->cost[j]);
        }
        printf("\n");
    }
}

