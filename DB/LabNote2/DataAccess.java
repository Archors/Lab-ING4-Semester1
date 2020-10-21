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
			conn.setAutoCommit(false);
		}
		catch(SQLException ex) {
			ex.printStackTrace();
		}
	}

	public void close(){
		try {
			conn.close();
		}
		catch(SQLException ex) {
			ex.printStackTrace();
		}
	}

	public void autoCommitOff()
	{
		try {
			conn.setAutoCommit(false);
		}catch(SQLException ex) {
			ex.printStackTrace();
		}
	}

	public void autoCommitOn()
	{
		try {
			conn.setAutoCommit(true);
		}catch(SQLException ex) {
			ex.printStackTrace();
		}
	}


	public int getCommitMode()
	{
		try {
			if(conn.getAutoCommit()){
				System.out.println(1);
				return 1;
			}
			else {
				System.out.println(0);
				return 0;
			}
		}catch(SQLException ex) {
			ex.printStackTrace();
		}
		return 2;
	}

	public int getTransactionLevelInt()
	{
		try {
			System.out.println(conn.getTransactionIsolation());
			return conn.getTransactionIsolation();
		}catch(SQLException ex) {
			ex.printStackTrace();
		}
		return 10;
	}

	public String getTransactionLevelString()
	{
		try {
			System.out.println(conn.getTransactionIsolation());
			switch(conn.getTransactionIsolation()) {
			case 0:
			{
				System.out.println("TRANSACTION_NONE");
				return("TRANSACTION_NONE");
			}
			case 1:
			{
				System.out.println("TRANSACTION_READ_UNCOMMITTED");
				return("TRANSACTION_READ_UNCOMMITTED");
			}
			case 2:
			{
				System.out.println("TRANSACTION_READ_COMMITTED");
				return("TRANSACTION_READ_COMMITTED");
			}
			case 4:
			{
				System.out.println("TRANSACTION_REPEATABLE_READ");
				return("TRANSACTION_REPEATABLE_READ");
			}
			case 8:
			{
				System.out.println("TRANSACTION_SERIALIZABLE");
				return("TRANSACTION_SERIALIZABLE");
			}
			default:
			{
				return("Error");
			}
			}
		}catch(SQLException ex) {
			ex.printStackTrace();
		}
		return "Error";
	}


	public List<EmployeeInfo> getEmployee()
	{
		List<EmployeeInfo> returnList = new ArrayList<>();
		try {
			conn.setAutoCommit(false);
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery("SELECT * FROM emp");
			while(rs.next()) {
				returnList.add(new EmployeeInfo(rs.getInt(1),rs.getString(2), rs.getFloat(6)));
			}
			conn.commit();
		}catch(SQLException e) {
			try {
				conn.rollback();
			}catch(SQLException ex) {
				ex.printStackTrace();
			}
		}
		return returnList;
	}

	boolean raiseSalary(String job, float amount)
	{
		boolean returnRaise = false;
		try {
			conn.setAutoCommit(false);
			Statement stmt = conn.createStatement();
			stmt.executeQuery("UPDATE emp SET salary = salary + "+amount+" WHERE job = "+job);
			conn.commit();
		}catch(SQLException e) {
			try {
				conn.rollback();
			}catch(SQLException ex) {
				ex.printStackTrace();
			}
		}
		return returnRaise;
	}

	public List<EmployeeInfo> getEmployeePS()
	{
		List<EmployeeInfo> returnList = new ArrayList<>();
		try {
			conn.setAutoCommit(false);
			PreparedStatement prep = conn.prepareStatement("SELECT * FROM emp");
			ResultSet rs = prep.executeQuery();
			while(rs.next()) {
				returnList.add(new EmployeeInfo(rs.getInt(1),rs.getString(2), rs.getFloat(6)));
			}
			conn.commit();
		}catch(SQLException e) {
			try {
				conn.rollback();
			}catch(SQLException ex) {
				ex.printStackTrace();
			}
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
			conn.commit();
			returnRaise = true;
		}catch(SQLException e) {
			try {
				conn.rollback();
			}catch(SQLException ex) {
				ex.printStackTrace();
			}
		}
		return returnRaise;
	}

	public List<DepartmentInfo> getDepartments(Integer id, String name, String location)
	{
		List<DepartmentInfo> returnList = new ArrayList<>();
		try {
			conn.setAutoCommit(false);
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery("SELECT *"
					+ " FROM    dept"
					+ " WHERE   (DID ="+id+" OR "+id+" IS NULL)"
					+ " AND     (DNAME ="+name+" OR "+name+" IS NULL)"
					+ " AND     (DLOC ="+location+" OR "+location+" IS NULL)");
			while(rs.next()) {
				returnList.add(new DepartmentInfo(rs.getInt(1),rs.getString(2), rs.getString(3)));
			}
			conn.commit();
		}catch(SQLException e) {
			try {
				conn.rollback();
			}catch(SQLException ex) {
				ex.printStackTrace();
			}
		}
		return returnList;
	}

	public List<DepartmentInfo> getDepartmentsPS(Integer id, String name, String location)
	{
		List<DepartmentInfo> returnList = new ArrayList<>();
		try {
			conn.setAutoCommit(false);
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
				returnList.add(new DepartmentInfo(rs.getInt(1),rs.getString(2), rs.getString(3)));
			}
			conn.commit();
		}catch(SQLException e) {
			try {
				conn.rollback();
			}catch(SQLException ex) {
				ex.printStackTrace();
			}
		}
		return returnList;
	}

	List<String> executeQuery(String query){
		List<String> returnList = new ArrayList<>();
		try {
			conn.setAutoCommit(false);
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(query);
			while(rs.next()) {
				returnList.add(rs.getString(1));
			}
			conn.commit();
		}catch(SQLException e) {
			try {
				conn.rollback();
			}catch(SQLException ex) {
				ex.printStackTrace();
			}
		}
		return returnList;
	}

	List<String> executeStatement(String statement){
		List<String> returnList = new ArrayList<>();
		try {
			conn.setAutoCommit(false);
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(statement);
			while(rs.next()) {
				returnList.add(rs.getString(1));
			}
			conn.commit();
		}catch(SQLException e) {
			try {
				conn.rollback();
			}catch(SQLException ex) {
				ex.printStackTrace();
			}
		}
		return returnList;
	}
}
