package test;

import model.DataAccess;

public class Test {

  public static void main(String[] args) throws Exception {
	  String url = "jdbc:mysql://localhost:3306/company";
	  String username = "root";
	  String pwd = "";
	  DataAccess data = new DataAccess(url, username,pwd);	 
	  data.getCommitMode();
	  data.getTransactionLevel();
	  //data.printEmployeePS();
	  data.close();
  }
}
