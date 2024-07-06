/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Logic;



import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.SQLException;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author sumit
 */
public class Listener {
     public static void main(String[] args) throws IOException, InterruptedException {
    	
        int count=0;
        boolean flag=false;
        BufferedWriter out = null;
        ServerSocket listener = new ServerSocket(9091);
         
        try{
            while(true){
                Socket socket = listener.accept();
                socket.setKeepAlive(true);
                System.out.println("Client Connected");
                try{
                    BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                    String data=in.readLine();
                    System.out.println("Client response: " + data);
                    out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
                   
                   
                    if(!data.equals(""))
                    {
                        if(data.endsWith("#"))
                        {
                            data=data+"NA";
                        }
                        System.out.println("Data "+data);
                        String a[]=data.split("#");
                        System.out.println("");
                        System.out.println(a[0]);// button
                        System.out.println(a[1]);// mq
                        System.out.println(a[2]);// tag
                       
                        if(!a[2].equals("NA"))
                        {
                           if(a[0].equals("1"))
                            {
                                System.out.println("Emergency Vehicle Detected in Road 1");
                                out.write("bcegjl");
                              
                                out.flush();
                               try {
                                   Thread.sleep(10000);
                               } catch (InterruptedException ex) {
                                   Logger.getLogger(Listener.class.getName()).log(Level.SEVERE, null, ex);
                               }
                                
                                
                              
                            }
                           else{
                           System.out.println("Emergency Vehicle Detected in Road 2");
                                out.write("adfhik");
                               
                                out.flush();
                               try {
                                   Thread.sleep(10000);
                               } catch (InterruptedException ex) {
                                   Logger.getLogger(Listener.class.getName()).log(Level.SEVERE, null, ex);
                               }
                           }
                          
                        
                        }
                           
                        else
                        {
                            System.out.println("Normal Mode");
                            if(flag==false)
                            {
                                System.out.println("sending isntruction");
                                
                                out.write("adfhjk");
                                out.flush();

                            }
                            else{
                                System.out.println("sending isntruction..");
                                out.write("bdegjl");
                               out.flush();
                                 
                            
                            }
                           
                            
                        
                        }
                        
                    String em="";
                    File file1 = new File("D:/density.txt"); 

                    BufferedReader br = new BufferedReader(new FileReader(file1)); 

                    String st; 
                    while ((st = br.readLine()) != null) {
                    System.out.println(st); 
                    em=st;
                    
                    }
                       
                    if(em.equalsIgnoreCase("rs1"))
                    {
                         System.out.println("Road 1 desnsity high");
                    out.write("bcegjl");
                              
                    out.flush();
                    
                    }
                    else{
                          System.out.println("Road 2 desnsity high");
                     out.write("adfhik");
                               
                                out.flush();
                    }
                        
                        
                        
       
                    }
                    
                    
                  //  out.flush();
                } finally {
                    socket.close();
                    System.out.println("count "+count);
                    count++;
                     if(count%10==0)
                            {
                                
                            if(flag==true)
                            {
                            flag=false;
                            }
                            else{
                            flag=true;
                            }
                           // count =0;
                            }
                    
                   
                }
            }
           } finally {
            listener.close();
          }
     }
     
     
    
     
     
}
