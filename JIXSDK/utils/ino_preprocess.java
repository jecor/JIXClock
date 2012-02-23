/*
 ino_preprocess - command line preprocessor for Arduino files
 
 Copyright (c) 2011 Jérôme Cornet
 
 Derived from PdePreprocessor from Arduino
 
 Copyright (c) 2004-05 Hernando Barragan
 
 Processing version Copyright (c) 2004-05 Ben Fry and Casey Reas
 Copyright (c) 2001-04 Massachusetts Institute of Technology
 
 ANTLR-generated parser and several supporting classes written
 by Dan Mosedale via funding from the Interaction Institute IVREA.
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software Foundation,
 Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

import java.io.*;
import java.util.*;

import java.util.regex.*;

public class ino_preprocess 
{
   /**
    * Strips comments, pre-processor directives, single- and double-quoted
    * strings from a string.
    * @param in the String to strip
    * @return the stripped String
    */
   public String strip(String in) {
      // XXX: doesn't properly handle special single-quoted characters
      // single-quoted character
      String p = "('.')";
      
      // double-quoted string
      p += "|(\"(?:[^\"\\\\]|\\\\.)*\")";
      
      // single and multi-line comment
      //p += "|" + "(//\\s*?$)|(/\\*\\s*?\\*/)";
      p += "|(//.*?$)|(/\\*[^*]*(?:\\*(?!/)[^*]*)*\\*/)";
      
      // pre-processor directive
      p += "|" + "(^\\s*#.*?$)";
      
      Pattern pattern = Pattern.compile(p, Pattern.MULTILINE);
      Matcher matcher = pattern.matcher(in);
      return matcher.replaceAll(" ");
   }
   
   /**
    * Removes the contents of all top-level curly brace pairs {}.
    * @param in the String to collapse
    * @return the collapsed String
    */
   private String collapseBraces(String in) {
      StringBuffer buffer = new StringBuffer();
      int nesting = 0;
      int start = 0;
      
      // XXX: need to keep newlines inside braces so we can determine the line
      // number of a prototype
      for (int i = 0; i < in.length(); i++) {
         if (in.charAt(i) == '{') {
            if (nesting == 0) {
               buffer.append(in.substring(start, i + 1));  // include the '{'
            }
            nesting++;
         }
         if (in.charAt(i) == '}') {
            nesting--;
            if (nesting == 0) {
               start = i; // include the '}'
            }
         }
      }
      
      buffer.append(in.substring(start));
      
      return buffer.toString();
   }
   
   public ArrayList<String> prototypes(String in) {
      in = collapseBraces(strip(in));
      
      // XXX: doesn't handle ... varargs
      // XXX: doesn't handle function pointers
      Pattern pattern = Pattern.compile("[\\w\\[\\]\\*]+\\s+[&\\[\\]\\*\\w\\s]+\\([&,\\[\\]\\*\\w\\s]*\\)(?=\\s*\\{)");
      
      ArrayList<String> matches = new ArrayList<String>();
      Matcher matcher = pattern.matcher(in);
      while (matcher.find())
         matches.add(matcher.group(0) + ";");
      
      return matches;
   }
   
   public ino_preprocess(String[] args)
   {
      if (args.length > 0)
      {
         for (int j=0; j<args.length; j++)
         {
            try
            {
               String text = new Scanner( new File(args[j]) ).useDelimiter("\\A").next();
                              
               List<String> prototypes = prototypes(text);
               
               for (int i = 0; i < prototypes.size(); i++) {
                  System.out.print(prototypes.get(i) + "\n");
               }
            }
            catch (FileNotFoundException e)
            {
               System.err.println("Unable to open input file!");
            }
         }
      }
   }
   
   public static void main(String[] args) 
   {
      new ino_preprocess(args);
   }
}
