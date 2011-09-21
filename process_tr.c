/********************************************************************************************************************************************/
/*		 	CREATE A LIST(PROCESS TREE)  OF PPIDS AND PIDS									  */
/*******************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>

main()
{
FILE *fp;
char strbuf[255];
char *rowptr , *tokptr;
int rowcount=0;
int colcount;
int parent_child[100][2];//changed
int parent[100][2];//changed
int child[100][2];
int ppid_count = 0;
int i,j,k,m;
int parchd_cnt;
char token[10];
signed int tokint;
int tcount,repeatppid,ccount;

fp = popen("ps -axl","r");

nextrow: while(!feof(fp))
      {
	rowptr = fgets(strbuf,255,fp);
	rowcount++; 
        
		if ((rowcount > 1)/* && (rowcount < 8)*/)
		{
		parchd_cnt = rowcount - 2;
		tokptr = strtok(rowptr, " ");
		colcount = 1;
			while (1)
			{
				tokptr = strtok(NULL, " ");
				if( tokptr == NULL)
					{
					goto nextrow;
					}
				colcount++;
				
				if ((colcount == 4)||(colcount == 5))
			{
                                        
					tokint = atoi(tokptr);
			}
			
				if (colcount == 5)
				{       if (ppid_count == 0)
                                	        {
						
					       parent[ppid_count][0] = tokint;//changed
						ppid_count++;			
						}

                                        else
						{tcount = 0;
							for(j=0; j<ppid_count; j++)
                                       			{
							 if (parent[j][0] == tokint)
							       	{ 
								 tcount++;
								}
					         	}
							if ((tcount ==  0))
						        {
								parent[ppid_count][0] = tokint;
						       		ppid_count++;
							 }
							
						}
					
                                	
					 parent_child[parchd_cnt][1] = tokint;
		  		}
		   		 if (colcount == 4)
                                {	
					parent_child[parchd_cnt][0] = tokint;
		                }
			       	
			}//while
               } //if     
	 }//while

for(i=0;i<ppid_count;i++)
 {repeatppid=0;
	printf("PPID\t\tPID\n");
	for(k=0;(k<parchd_cnt);k++)
	{ccount=0;
		if ( parent[i][0] == parent_child[k][1])
		    {	repeatppid++;
			if (repeatppid == 1)
			   {
				printf("%d\t\t%d\n",parent_child[k][1],parent_child[k][0]);
				child[repeatppid-1][0] = parent_child[k][0];
			   }
			else
			   {/*
				for(m=0; m<repeatppid;m++)
			     	   { if (child[m][0] == parent_child[k][0])	
					ccount++;
				   }
                           	if (ccount ==  0 )*/ 
               			 printf("\t\t%d\n",parent_child[k][0]);
                           }
		   }
	}
 }

pclose(fp);
}
 
