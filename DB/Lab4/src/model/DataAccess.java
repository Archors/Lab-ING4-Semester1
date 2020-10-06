package model;

import java.sql.*;	
import java.util.*;

public class DataAccess {
	
	Connection conn = null;

  public DataAccess(String url, String login, String password) throws
      SQLException {
    try{
    	conn = DriverManager.getConnection(url, login, password);
        System.out.println("connected to " + url);
    }
    catch(SQLException e) {
    	System.err.println("Connexion problem");
    }
  }
  
  public void close(){
	  try {
		  conn.close();
	  }
	  catch(SQLException e) {
	    	System.err.println("Connexion problem");
	  }
  }

  
  public List<EmployeeInfo> getEmployee()
  {
	  List<EmployeeInfo> returnList = new ArrayList<>();
	  try {
		  Statement stmt = conn.createStatement();
		  ResultSet rs = stmt.executeQuery("SELECT * FROM emp");
		  while(rs.next()) {
			  returnList.add(new EmployeeInfo(rs.getInt(1),rs.getString(1), rs.getFloat(2)));
		  }
		  }catch(SQLException ex) {
			  System.err.println("The query isn't possible");
		  }
	  return returnList;
  }
  
  boolean raiseSalary(String job, float amount)
  {
	  boolean returnRaise = false;
	  try {
		  Statement stmt = conn.createStatement();
		  stmt.executeQuery("UPDATE emp SET salary = salary + "+amount+" WHERE job = "+job);
	  }catch(SQLException ex) {
	  System.err.println("The query isn't possible");
  }
	  return returnRaise;
  }
  
  public List<EmployeeInfo> getEmployeePS()
  {
	  List<EmployeeInfo> returnList = new ArrayList<>();
	  try {
		  PreparedStatement prep = conn.prepareStatement("SELECT * FROM emp");
		  ResultSet rs = prep.executeQuery();
		  while(rs.next()) {
			  returnList.add(new EmployeeInfo(rs.getInt(1),rs.getString(1), rs.getFloat(2)));
		  }
		  }catch(SQLException ex) {
			  System.err.println("The query isn't possible");
		  }
	  return returnList;
  }
  
  boolean raiseSalaryPS(String job, float amount)
  {
	  boolean returnRaise = false;
	  try {
		  PreparedStatement prep = conn.prepareStatement("UPDATE emp SET salary = ? + WHERE job = ?");
		  prep.setString(1, job);
		  prep.setFloat(1,amount);
		  returnRaise = true;
	  }catch(SQLException ex) {
	  System.err.println("The query isn't possible");
	  returnRaise = false;
  }
	  return returnRaise;
  }
  
  public List<DepartmentInfo> getDepartments(Integer id, String name, String location)
  {
  	  List<DepartmentInfo> returnList = new ArrayList<>();
  	  try {
  		  Statement stmt = conn.createStatement();
		  ResultSet rs = stmt.executeQuery("SELECT *"
	  		  		+ " FROM    dept"
	  		  		+ " WHERE   (DID ="+id+" OR "+id+" IS NULL)"
	  		  		+ " AND     (DNAME ="+name+" OR "+name+" IS NULL)"
	  		  		+ " AND     (DLOC ="+location+" OR "+location+" IS NULL)");
  		  while(rs.next()) {
  			  returnList.add(new DepartmentInfo(rs.getInt(1),rs.getString(1), rs.getString(2)));
  		  }
  		  }catch(SQLException ex) {
  			  System.err.println("The query isn't possible");
  		  }
  	  return returnList;
  }
  
  public List<DepartmentInfo> getDepartmentsPS(Integer id, String name, String location)
  {
  	  List<DepartmentInfo> returnList = new ArrayList<>();
  	  try {
  		  PreparedStatement prep = conn.prepareStatement("SELECT *"
  		  		+ " FROM    dept"
  		  		+ " WHERE   (DID = ? OR ? IS NULL)"
  		  		+ " AND     (DNAME = ? OR ? IS NULL)"
  		  		+ " AND     (DLOC = ? OR ? IS NULL)");
  		  ResultSet rs = prep.executeQuery();
  		  prep.setInt(1, id);
  		  prep.setInt(2, id);
  		  prep.setString(1, name);
  		  prep.setString(2, name);
  		  prep.setString(3, location);
  		  prep.setString(4, location);
  		  while(rs.next()) {
  			  returnList.add(new DepartmentInfo(rs.getInt(1),rs.getString(1), rs.getString(2)));
  		  }
  		  }catch(SQLException ex) {
  			  System.err.println("The query isn't possible");
  		  }
  	  return returnList;
  }
  
  List<String> executeQuery(String query){
	  List<String> returnList = new ArrayList<>();
	  	try {
	  		Statement stmt = conn.createStatement();
	  		ResultSet rs = stmt.executeQuery(query);
	  		while(rs.next()) {
	  			  returnList.add(rs.getString(1));
	  		  }
	  	}catch(SQLException ex) {
	  		System.err.println("The query isn't possible");
	  	}
	  	return returnList;
  }
  
  List<String> executeStatement(String statement){
	  List<String> returnList = new ArrayList<>();
	  	try {
	  		Statement stmt = conn.createStatement();
	  		ResultSet rs = stmt.executeQuery(statement);
	  		while(rs.next()) {
	  			  returnList.add(rs.getString(1));
	  		  }
	  	}catch(SQLException ex) {
	  		System.err.println("The query isn't possible");
	  	}
	  	return returnList;
  }

}
