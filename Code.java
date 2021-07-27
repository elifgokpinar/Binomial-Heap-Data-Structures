//hw3 elif.gokpinar and gizem.celik
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Code {

	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		 File file = new File("test-input-1.txt");   //we read input and wrote input with this names
		 PrintWriter pw = new PrintWriter("test-output-1.txt");
		 Scanner input = new Scanner(file);
		 ArrayList<city> citys = new ArrayList<city>(); //we created city arraylist for citys in inputs.
		 
		 int totalcity = 0;
	
		 String line = ""; //for input line
	
		 while(input.hasNextLine()) {
	    	line = input.nextLine();
			 String[] c = line.split("\\s+"); //we used split function while taking input lines
			 
			 if(c[0].equals("")  ) //if there is space char in input line, read next info's as next split array
			 {
				 double id = Double.parseDouble(c[1]);
					double x = Double.parseDouble(c[2]);
					double y = Double.parseDouble(c[3]);
					citys.add(new city(id,x,y)); //we created cities with these info's and we stored them in arraylist.
					totalcity++;
					continue;
			 }
			 
			double id = Double.parseDouble(c[0]);  //if there is no whitespace in beginning of the line, then take infos with starting from 0
			double x = Double.parseDouble(c[1]);
			double y = Double.parseDouble(c[2]);
			
			citys.add(new city(id,x,y));//we created cities with these info's and we stored them in arraylist.
			
			totalcity++;
		 }
	
		 
		int[][] adjaceny = new int[totalcity][totalcity]; //we created adjaceny matrix for storing distances between cities.
		 
		// We calculated and stored distance values of cities in this two for loop.
		 
		 
		 for( int i = 0 ;i < totalcity ; i++) {
				for(int j = 0 ; j < totalcity ; j++) {
					if(i==j) {
						adjaceny[i][j]=0;
					}
					else {
						
						double distance = Math.round(dist(citys.get(i).x,citys.get(i).y,citys.get(j).x,citys.get(j).y));
					
						adjaceny[i][j]=(int)distance;
					}
					  
					  }
				} //for end
		 
		 double path = 0;
		 int ind=0;
		 double shortPath=0;
		 int optj = 0;
		 double temp=0;
		 int opts = 0;
		 int i = 0;
		 int start = 0;
		 
		 
		  //For each starting point e calculated their shortest paths in the end, we selected minimal distance.
		  
		 for(int b = 0; b < citys.size() ; b++ ) {
			 citys.get(b).visited = true;  //if city is visited
			 ind = b; //make start index to b
			 path =0; 
			 start = b; //holds starting city index
		
		       for(i = 0; i < citys.size() ; i++ ) {
			 shortPath =1000000000; //setting max value to shortest value
			 
			        for(int j = 0; j < citys.size() ; j++ ) { //travelling around other cities 
				  
				        if(shortPath >= adjaceny[ind][j] && !citys.get(j).visited && ind!=j) { //if initial short distance is smaller than before distance
					  //new short point is this
					   shortPath = adjaceny[ind][j];
					   optj = j;
				   }
						 continue;
			 } 
			 
			 if(i == citys.size()-1) { //for end point 
				 path+= adjaceny[start][optj];
			
			 }
			 else {
				 path+= shortPath;
			 }
			
			 
			 citys.get(optj).visited = true;//If city is visited
			 ind = optj; //Go next city,nearest point's id.
		 } 
		    
		    if(b==0) {//If the first time for the visiting
		    	temp = path;
				    for(int c = 0; c < citys.size() ; c++ )
				    	 citys.get(c).visited = false;
		    	continue;
		    	
		    }
		    if(path<temp) {//If the path is smaller than temp
				 temp =path;
				 opts = b;//In the end,optimum starting point
			 }
			 
		    for(int c = 0; c < citys.size() ; c++ )
		    	 citys.get(c).visited = false;  //Assume the cities are not visited for next starting path
		 }
		 pw.println((int)temp); //printing optimal tour
		 
		 //--------------------------------------------------------------------------
		 path = 0;
		 ind=opts;//selecting starting city' id  with optimal tour's starting id
		 shortPath=0;
		 optj = 0;
		 
		 citys.get(ind).visited = true;
		 pw.println(opts);
		 for(i = 0; i < citys.size() ; i++ ) { //this part is similar as before this part
			
			 shortPath =1000000000; 
			 
			 for(int j = 0; j < citys.size() ; j++ ) {
				  
				   if(shortPath >= adjaceny[ind][j] && !citys.get(j).visited && ind!=j) {//Find the shortest path
					  
					   shortPath = adjaceny[ind][j];
					   optj = j;
				   }
						 continue;
			 }
			 
			 if(i == citys.size()-1) {//If the point is in the last city
				 path+= adjaceny[opts][optj];
			 }
			 else {
				 path+= shortPath;
				pw.println(optj);
			 }

			 citys.get(optj).visited = true;
			 ind = optj;//Go next city
		 }
		 pw.close();		 
			} 
		 
	public static double dist(double x1,double y1,double x2,double y2) {//Find the distance between two cities
		   double y = y2 -y1;
		   double x = x2-x1;
		   
		   double dis =  Math.pow(y, 2) + Math.pow(x, 2);   //calculating distance between two points
		   double dist = Math.sqrt(dis);
		   return dist;
	   }
	} 

class city { //creating city object
	public double id;
	public double x;
	public double y;
	public boolean visited;

	public city (double id,double x,double y){
		this.id = id;
		this.x = x;
		this.y = y;
		this.visited=false;
	}
}
