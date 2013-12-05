import java.sql.*;
import java.io.*;

public class Blob{

public static void main(String args[]){

PreparedStatement pstmt;
ResultSet rs = null;

try {
Class.forName("com.mysql.jdbc.Driver");

String url ="jdbc:mysql://localhost:3306/asenovh";
Connection conn = DriverManager.getConnection(url,"asenovh", "0920");

String filename = args[0];
InputStream filecontent = new FileInputStream(filename);

String sql = "UPDATE Item SET image = ? where iid = " + args[1];

int size = filecontent.available();
PreparedStatement ps = conn.prepareStatement(sql);
ps.setBinaryStream(1, filecontent, size);
ps.executeUpdate();

sql = "SELECT image FROM Item where iid = " + args[1];

ps  = conn.prepareStatement(sql);
rs  = ps.executeQuery();

if (rs.next()){
    InputStream contentStream = rs.getBinaryStream("image");
    String newFilename = "new_" + filename;
    // storing the input stream in the file

    OutputStream out=new FileOutputStream(newFilename);
    byte buf[]=new byte[1024];
    int len;
    while((len=contentStream.read(buf))>0)

    out.write(buf,0,len);
    out.close();
}
conn.close();
}

catch (Exception e) {
       System.out.println("Exception is " + e);
}
}
}
