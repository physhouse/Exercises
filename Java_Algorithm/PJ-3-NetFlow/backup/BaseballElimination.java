import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.FlowNetwork;
import edu.princeton.cs.algs4.FlowEdge;
import edu.princeton.cs.algs4.FordFulkerson;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.Iterator;


public class BaseballElimination
{
  private class teamInfo
  {
    private String team;
	private int wins;
	private int losses;
	private int remaining;
	teamInfo(String teamName, int wins, int losses, int remaining)
	{
	  this.team = teamName;
	  this.wins = wins;
	  this.losses = losses;
	  this.remaining = remaining;
	}
  }

  private ArrayList<teamInfo> teamList;
  private HashMap<String, Integer> team2id;
  private int numTeams;
  private int[][] againstTable;

  public BaseballElimination(String filename)
  {
	team2id = new HashMap<String, Integer>();
    teamList = new ArrayList<teamInfo>();
    In input = new In(filename);
    numTeams = input.readInt();
   
	againstTable = new int[numTeams][numTeams];

	for (int iline=0; iline<numTeams; iline++)
	{
      String teamName = input.readString();

	  int wins_line = input.readInt();
	  int losses_line = input.readInt();
	  int remaining_line = input.readInt();
	  teamInfo team = new teamInfo(teamName, wins_line, losses_line, remaining_line);
	  teamList.add(team);
	  team2id.put(teamName, iline);

	  //Generating the matrix
	  for (int i=0; i<numTeams; i++) 
	  {
	    againstTable[iline][i] = input.readInt();
		//StdOut.print(againstTable[iline][i]+" ");
	  }
	  //StdOut.println("--");
	}

  }

  public int numberOfTeams()
  {
     return numTeams;
  }

  public Iterable<String> teams()
  {
     return team2id.keySet();
  }

  public int wins(String team)
  {
     return teamList.get(team2id.get(team)).wins; 
  }

  public int losses(String team)
  {
     return teamList.get(team2id.get(team)).losses; 
  }

  public int remaining(String team)
  {
     return teamList.get(team2id.get(team)).remaining; 
  }

  public int against(String team1, String team2)
  {
     return againstTable[team2id.get(team1)][team2id.get(team2)];
  }

  public FlowNetwork generateFlow(int id)
  {
    int size = 1 + ((numTeams - 1)*(numTeams - 2))/2 + (numTeams - 1) + 1;
	FlowNetwork matchNet = new FlowNetwork(size);
	int tid = id;
	
	int indexLevelOne = 1;
	for (int i=0; i<numTeams; i++)
	{
	  if (i == tid) continue;
	  for (int j=i+1; j<numTeams; j++)
	  {
	    if (j == tid) continue;
		FlowEdge fe = new FlowEdge(0, indexLevelOne, againstTable[i][j]);
		matchNet.addEdge(fe);
		indexLevelOne++;
	  }
	}

    int offset = ((numTeams - 1) * (numTeams - 2)) / 2;
	int round = 1;
	int index = 1;

	while (round <= (numTeams - 2))
	{
	  int entries = numTeams - 1 - round;
	  for(int k=1; k<=entries; k++)
	  {
	    FlowEdge fe1 = new FlowEdge(index, offset + round, Double.POSITIVE_INFINITY);
		FlowEdge fe2 = new FlowEdge(index, offset + round + k, Double.POSITIVE_INFINITY);
		matchNet.addEdge(fe1);
		matchNet.addEdge(fe2);
		index++;
	  }
	  round++;
	}

    int maxt = teamList.get(tid).wins + teamList.get(tid).remaining;
	for (int i=0; i<numTeams-1; i++)
	{
	  int id_team;
	  if (tid > i) id_team = i;
	  else id_team = i + 1;

	  int id_remaining = teamList.get(id_team).wins;
	  int remainWins = maxt - id_remaining;
	  if (remainWins < 0) remainWins = 0;
	  FlowEdge fe = new FlowEdge(offset+i+1, size-1, remainWins);
	  matchNet.addEdge(fe);
	}

	return matchNet;
  } 

  public boolean isEliminated(String team)
  {
     int tid = team2id.get(team);
     int size = 1 + ((numTeams - 1)*(numTeams - 2))/2 + (numTeams - 1) + 1;
	 FlowNetwork flow = generateFlow(tid);
	 FordFulkerson ff = new FordFulkerson(flow, 0, size-1);
	 double maxflow = ff.value();
	 double maxCapacity = 0;

	 for (int i=0; i<numTeams; i++)
	 {
	   if (i == tid) continue;
	   for (int j=i+1; j<numTeams; j++)
	   {
	     if (j == tid) continue;
		 else maxCapacity += againstTable[i][j];
	   }
	 }

	 if (maxCapacity > maxflow)
	    return true;

     return false;
  }

  public Iterable<String> certificateOfElimination(String team)
  {
     ArrayList<String> vertices = new ArrayList<String>();
     int tid = team2id.get(team);
     int size = 1 + ((numTeams - 1)*(numTeams - 2))/2 + (numTeams - 1) + 1;
	 FlowNetwork flow = generateFlow(tid);
	 FordFulkerson ff = new FordFulkerson(flow, 0, size-1);
     int offset = ((numTeams - 1) * (numTeams - 2)) / 2;

	 for (int i=0; i<numTeams-1; i++)
	 {
	    if(ff.inCut(offset+i+1))
		{
		  if (tid > i) vertices.add(teamList.get(i).team);
		  else vertices.add(teamList.get(i+1).team);
		}
	 }
	 
	 return vertices;
  }

  public static void main(String[] args) {
      //BaseballElimination be = new BaseballElimination(args[0]);
	  //StdOut.println(be.teams());
	  //int id = Integer.parseInt(args[1]);
	  //FlowNetwork fn = be.generateFlow(id);
	  //String network = fn.toString();
	  //for (String v : be.teams())
        //StdOut.println(v+"  "+be.isEliminated(v));
	  //StdOut.println(network);
      BaseballElimination division = new BaseballElimination(args[0]);
	  for (String team : division.teams()) {
		if (division.isEliminated(team)) {
		   StdOut.print(team + " is eliminated by the subset R = { ");
		   for (String t : division.certificateOfElimination(team)) {
			  StdOut.print(t + " ");
		   }
		   StdOut.println("}");
		}
		else {
          StdOut.println(team + " is not eliminated");
        }
	  }
  }

}
