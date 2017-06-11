/*
 * Licensed to the Apache Software Foundation (ASF) under one or more

 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// 

/* 
 	CS362_400_S2017
 	Final Project - Part B
 	6/11/2017
 
 	Group Members:
 		* Alex Giesbrecht - giesbral@oregonstate.edu
 		* Michael Sterrir - sterritm@oregonstate.edu
 		* Ian Stanfield - stanfiei@oregonstate.edu
*/

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ErrorCollector;
import static org.hamcrest.CoreMatchers.*;

import org.hamcrest.CoreMatchers;

import junit.framework.TestCase;


/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   //my urls
	   System.out.println(urlVal.isValid("http://www.google.com"));
	   
	   //schemes
	   //no scheme
	   System.out.println("no scheme");
	   System.out.println(urlVal.isValid("www.google.com"));
	   
	   //another valid scheme
	   System.out.println("valid scheme");
	   System.out.println(urlVal.isValid("ftp://www.google.com"));
	   
	   //invalid scheme
	   System.out.println("Random string scheme");
	   System.out.println(urlVal.isValid("asdgasdfg://www.google.com"));	//true,  returns true for random string
	   
	   //scheme missing char
	   System.out.println("scheme - start with number");
	   System.out.println(urlVal.isValid("3htp://www.google.com"));
	   
	   System.out.println("scheme - with number");
	   System.out.println(urlVal.isValid("htt3p://www.google.com"));
	   
	   System.out.println("scheme - ://");
	   System.out.println(urlVal.isValid("://www.google.com"));
	   
	   System.out.println("scheme - :/");
	   System.out.println(urlVal.isValid("http:/www.google.com"));
	   
	   System.out.println("scheme - //");
	   System.out.println(urlVal.isValid("http//www.google.com"));
	   
	   System.out.println("scheme - :");
	   System.out.println(urlVal.isValid("http:www.google.com"));
	   
	   //host
	   //valid host
	   System.out.println("valid host");
	   System.out.println(urlVal.isValid("http://www.google.com"));
	   
	   //valid numeric host
	   System.out.println("0.0.0.0");
	   System.out.println(urlVal.isValid("http://0.0.0.0"));
	   
	   //negative numeric host
	   System.out.println("invalid numeric - negative");
	   System.out.println(urlVal.isValid("-1.2.3.4"));
	   
	   //valid numeric host - max
	   System.out.println("valid numeric - max");
	   System.out.println(urlVal.isValid("http://255.255.255.255"));
	   
	   //invalid numeric host - exceeds max
	   System.out.println("invalid numeric - exceeds max (256)");
	   System.out.println(urlVal.isValid("http://256.256.256.256"));	//bug
	   
	   // no host
	   System.out.println("no host");
	   System.out.println(urlVal.isValid("http://"));
	   
	   //domains - list at https://en.wikipedia.org/wiki/List_of_Internet_top-level_domains
	   //original top-level domains
	   System.out.println("top level domains");
	   System.out.println(urlVal.isValid("http://www.google.com"));
	   System.out.println(urlVal.isValid("http://www.google.org"));
	   System.out.println(urlVal.isValid("http://www.google.edu"));
	   System.out.println(urlVal.isValid("http://www.google.net"));
	   
	   //country code top-level domains
	   System.out.println("Foreign domains");
	   System.out.println(urlVal.isValid("http://www.google.jp"));	//japan  - bug returned false
	   System.out.println(urlVal.isValid("http://www.google.au"));	//australia
	   System.out.println(urlVal.isValid("http://www.google.ca"));	//canada
	   System.out.println(urlVal.isValid("http://www.google.eu"));	//europe
	   System.out.println(urlVal.isValid("http://www.google.cn"));	//china
	   
	   //ICANN-era generic top-level domains
	   System.out.println("Various other valid domains");
	   System.out.println(urlVal.isValid("http://www.google.bike"));
	   System.out.println(urlVal.isValid("http://www.google.app"));
	   System.out.println(urlVal.isValid("http://www.google.art"));
	   System.out.println(urlVal.isValid("http://www.google.cards"));
	  
	   //invalid domains
	   System.out.println("invalid domains");
	   System.out.println(urlVal.isValid("http://www.google."));
	   System.out.println(urlVal.isValid("http://www.google.wer"));
	   System.out.println(urlVal.isValid("http://www.google.1234"));
	   System.out.println(urlVal.isValid("http://www.google.!!!!"));
	   
	   //ports
	   System.out.println("Valid port - 80");
	   System.out.println(urlVal.isValid("http://www.google.com:80"));
	   
	   System.out.println("Valid port - 0 (min)");
	   System.out.println(urlVal.isValid("http://www.google.com:0"));
	   
	   System.out.println("Valid port - 65535 (max)");
	   System.out.println(urlVal.isValid("http://www.google.com:65535"));	//bug - returns false
	   
	   System.out.println("Invalid port - -1");
	   System.out.println(urlVal.isValid("http://www.google.com:-1"));
	   
	   System.out.println("Invalid port - 65536");
	   System.out.println(urlVal.isValid("http://www.google.com:65536"));
	   
	   System.out.println("Invalid port - none");
	   System.out.println(urlVal.isValid("http://www.google.com:"));
	   
	   System.out.println("Invalid port - letters");
	   System.out.println(urlVal.isValid("http://www.google.com:abc"));
	   
	   //path
	   System.out.println("Valid path - /path/to/go");
	   System.out.println(urlVal.isValid("http://www.google.com/path/to/go"));
	   
	   System.out.println("Valid path - end with /");
	   System.out.println(urlVal.isValid("http://www.google.com/path/to/go/"));
	   
	   System.out.println("Valid path - no path");
	   System.out.println(urlVal.isValid("http://www.google.com/"));
	   
	   System.out.println("Invalid path - numbers");
	   System.out.println(urlVal.isValid("http://www.google.com/1/2/3"));
	   
	   System.out.println("Invalid path - start with //");
	   System.out.println(urlVal.isValid("http://www.google.com//path/to/go"));
	   
	   System.out.println("Invalid path - // in middle of path");
	   System.out.println(urlVal.isValid("http://www.google.com/path//to/go"));
	   
	   System.out.println("Invalid path - // at end of path");
	   System.out.println(urlVal.isValid("http://www.google.com/path/to/go//"));
	   
	   //query
	   System.out.println("Valid query - ?key=value");
	   System.out.println(urlVal.isValid("http://www.google.com/path?key=value"));		//bug - bug with ?
	   
	   System.out.println("Valid query - ?abcdefg");
	   System.out.println(urlVal.isValid("http://www.google.com/path?abcdefg"));
	   
	   System.out.println("Valid query - empty");
	   System.out.println(urlVal.isValid("http://www.google.com/path"));
	   
	   System.out.println("Invalid query - key=value (no ? mark)");
	   System.out.println(urlVal.isValid("http://www.google.com/path/key=value"));	//becomes part of path
	   
	   System.out.println("Valid query - ampersand seperator");
	   System.out.println(urlVal.isValid("http://www.google.com/path?key=value&bob=bill"));
	   
	   System.out.println("Valid query - semi colon seperator");
	   System.out.println(urlVal.isValid("http://www.google.com/path?key=value;bob=bill"));

   }
   
   public void testIsValid()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.ALLOW_LOCAL_URLS);
	   int numFailed = 0;
	   
//	   collector.addError(new Throwable("The actual is not equal to expected"));
	   
	   for (int i = 0; i < scheme.length; ++i)
	   {   	 
		   for (int j = 0; j < authority.length; ++j)
		   {
			   for (int k = 0; k < port.length; ++k)
			   {
				   for (int l = 0; l < path.length; ++l)
				   {
					   for (int a = 0; a < query.length; ++a) {
						   
						   StringBuffer urlBuffer = new StringBuffer();
						   boolean expected = true;
						   
						   urlBuffer.append(scheme[i].item);
						   expected &= scheme[i].valid;
								   
						   urlBuffer.append(authority[j].item);
						   expected &= authority[j].valid;
						   
						   urlBuffer.append(port[k].item);
						   expected &= port[k].valid;
						   
						   urlBuffer.append(path[l].item);
						   expected &= path[l].valid;
						  					   
						   urlBuffer.append(query[a].item);
						   expected &= query[a].valid;
						   
						   String urlString = urlBuffer.toString();
						   boolean actual = urlVal.isValid(urlString);
						   
						   if (!assertEqual(expected, actual)) {
							   numFailed++;
							   System.out.println("****FAIL " + numFailed + ": \"" + urlString + "\" was validated incorrectly. ---> expected: " + expected + ", actual: " + actual + "*****");
							   System.out.println("****FAILURE EXPECTATIONS --- SCHEME: " + scheme[i].valid + ", AUTHORITY: " + authority[j].valid + ", PORT: " + port[k].valid + ", PATH: " + path[l].valid + ", QUERY: " + query[a].valid + "*****");
							   System.out.println("");
						   };
					   }
				   }
			   }
		   }
	   }
	   
	   System.out.println("TOTAL FAILED TESTS: " + numFailed);
   }
   
   private boolean assertEqual(boolean expected, boolean actual)
   {
	   if (expected == actual)
	   {
		   return true;
	   }
	   else
	   {
		   return false;
	   }
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   
   ResultPair[] scheme = {	new ResultPair("https://", true),
		   					new ResultPair("http://", true),
		   					new ResultPair("dank://", true),
		   					new ResultPair("ftp://", true),
		   					new ResultPair("aaa://", true),
		   					new ResultPair("+aaa://", false),
		   					new ResultPair("attachment://", true),
		   					new ResultPair("jabber://", true),
		   					new ResultPair("z39.50s://", true),
		   					new ResultPair("121321://", false),
		   					new ResultPair("https:/", false),
		   					new ResultPair("http:", false),
		   					new ResultPair("http//", false),
		   					new ResultPair("http/", false),
		   					new ResultPair("://", false),
		   					new ResultPair("/", false),
		   					new ResultPair(":", false),		   					
		   					new ResultPair(" https://", false),
		   					new ResultPair("\'https://\'", false),
		   					new ResultPair(".http://", false),
		   					new ResultPair("-https://", false),
		   					new ResultPair("~https://", false),
		   					new ResultPair("", false)
		   					};
   
   ResultPair[] authority = {	// Testing standard hostnames
		   						new ResultPair("google.com", true),
		   						new ResultPair(" google.com", false),
		   						new ResultPair("göögle.com", false),		   							   						
		   						
		   						// Testing IP addresses
		   						new ResultPair("0.0.0.0", true),
		   						new ResultPair("-1.1.1.1", false),
		   						new ResultPair(".1.1.1.1", false),
		   						new ResultPair("1.1.1.1.", false),
		   						new ResultPair("1.1.1", false),
		   						new ResultPair("1.1.1.1.1", false),
		   						new ResultPair("256.255.255.255", false),
		   						new ResultPair("255.255.255.255", true),
		   						new ResultPair("255.255.255.0", true),
		   						new ResultPair("123.456.789.0", false),
		   						new ResultPair("244.244.244.0", true),
		   						
		   						// Testing Local URLs
		   						new ResultPair("localhost", true),
		   						new ResultPair("machine", true),
	   						
		   						// Testing URLs with invalid domain names
		   						new ResultPair(".com", false),
		   						new ResultPair(" ", false),
		   						
		   						// Testing Top-Level Domain Country Codes
		   						new ResultPair ("google.ad", true), 
		   						new ResultPair ("google.ae", true), 
		   						new ResultPair ("google.af", true), 
		   						new ResultPair ("google.ag", true), 
		   						new ResultPair ("google.ai", true), 
		   						new ResultPair ("google.al", true), 
		   						new ResultPair ("google.am", true), 
		   						new ResultPair ("google.an", true), 
		   						new ResultPair ("google.ao", true), 
		   						new ResultPair ("google.aq", true), 
		   						new ResultPair ("google.ar", true), 
		   						new ResultPair ("google.as", true), 
		   						new ResultPair ("google.at", true), 
		   						new ResultPair ("google.au", true), 
		   						new ResultPair ("google.aw", true), 
		   						new ResultPair ("google.ax", true), 
		   						new ResultPair ("google.az", true), 
		   						new ResultPair ("google.ba", true), 
		   						new ResultPair ("google.bb", true), 
		   						new ResultPair ("google.bd", true), 
		   						new ResultPair ("google.be", true), 
		   						new ResultPair ("google.bf", true), 
		   						new ResultPair ("google.bg", true), 
		   						new ResultPair ("google.bh", true), 
		   						new ResultPair ("google.bi", true), 
		   						new ResultPair ("google.bj", true), 
		   						new ResultPair ("google.bm", true), 
		   						new ResultPair ("google.bn", true), 
		   						new ResultPair ("google.bo", true), 
		   						new ResultPair ("google.br", true), 
		   						new ResultPair ("google.bs", true), 
		   						new ResultPair ("google.bt", true), 
		   						new ResultPair ("google.bv", true), 
		   						new ResultPair ("google.bw", true), 
		   						new ResultPair ("google.by", true), 
		   						new ResultPair ("google.bz", true), 
		   						new ResultPair ("google.ca", true), 
		   						new ResultPair ("google.cc", true), 
		   						new ResultPair ("google.cd", true), 
		   						new ResultPair ("google.cf", true), 
		   						new ResultPair ("google.cg", true), 
		   						new ResultPair ("google.ch", true), 
		   						new ResultPair ("google.ci", true), 
		   						new ResultPair ("google.ck", true), 
		   						new ResultPair ("google.cl", true), 
		   						new ResultPair ("google.cm", true), 
		   						new ResultPair ("google.cn", true), 
		   						new ResultPair ("google.co", true), 
		   						new ResultPair ("google.cr", true), 
		   						new ResultPair ("google.cu", true), 
		   						new ResultPair ("google.cv", true), 
		   						new ResultPair ("google.cx", true), 
		   						new ResultPair ("google.cy", true), 
		   						new ResultPair ("google.cz", true), 
		   						new ResultPair ("google.de", true), 
		   						new ResultPair ("google.dj", true), 
		   						new ResultPair ("google.dk", true), 
		   						new ResultPair ("google.dm", true), 
		   						new ResultPair ("google.do", true), 
		   						new ResultPair ("google.dz", true), 
		   						new ResultPair ("google.ec", true), 
		   						new ResultPair ("google.ee", true), 
		   						new ResultPair ("google.eg", true), 
		   						new ResultPair ("google.er", true), 
		   						new ResultPair ("google.es", true), 
		   						new ResultPair ("google.et", true), 
		   						new ResultPair ("google.eu", true), 
		   						new ResultPair ("google.fi", true), 
		   						new ResultPair ("google.fj", true), 
		   						new ResultPair ("google.fk", true), 
		   						new ResultPair ("google.fm", true), 
		   						new ResultPair ("google.fo", true), 
		   						new ResultPair ("google.fr", true), 
		   						new ResultPair ("google.ga", true), 
		   						new ResultPair ("google.gb", true), 
		   						new ResultPair ("google.gd", true), 
		   						new ResultPair ("google.ge", true), 
		   						new ResultPair ("google.gf", true), 
		   						new ResultPair ("google.gg", true), 
		   						new ResultPair ("google.gh", true), 
		   						new ResultPair ("google.gi", true), 
		   						new ResultPair ("google.gl", true), 
		   						new ResultPair ("google.gm", true), 
		   						new ResultPair ("google.gn", true), 
		   						new ResultPair ("google.gp", true), 
		   						new ResultPair ("google.gq", true), 
		   						new ResultPair ("google.gr", true), 
		   						new ResultPair ("google.gs", true), 
		   						new ResultPair ("google.gt", true), 
		   						new ResultPair ("google.gu", true), 
		   						new ResultPair ("google.gw", true), 
		   						new ResultPair ("google.gy", true), 
		   						new ResultPair ("google.hk", true), 
		   						new ResultPair ("google.hm", true), 
		   						new ResultPair ("google.hn", true), 
		   						new ResultPair ("google.hr", true), 
		   						new ResultPair ("google.ht", true), 
		   						new ResultPair ("google.hu", true), 
		   						new ResultPair ("google.id", true), 
		   						new ResultPair ("google.ie", true), 
		   						new ResultPair ("google.il", true), 
		   						new ResultPair ("google.im", true), 
		   						new ResultPair ("google.in", true), 
		   						new ResultPair ("google.io", true), 
		   						new ResultPair ("google.iq", true), 
		   						new ResultPair ("google.ir", true), 
		   						new ResultPair ("google.is", true), 
		   						new ResultPair ("google.it", true),
		   						new ResultPair ("google.je", true), 
		   						new ResultPair ("google.jm", true), 
		   						new ResultPair ("google.jo", true), 
		   						new ResultPair ("google.jp", true), 
		   						new ResultPair ("google.ke", true), 
		   						new ResultPair ("google.kg", true), 
		   						new ResultPair ("google.kh", true), 
		   						new ResultPair ("google.ki", true), 
		   						new ResultPair ("google.km", true), 
		   						new ResultPair ("google.kn", true), 
		   						new ResultPair ("google.kp", true), 
		   						new ResultPair ("google.kr", true), 
		   						new ResultPair ("google.kw", true), 
		   						new ResultPair ("google.ky", true), 
		   						new ResultPair ("google.kz", true), 
		   						new ResultPair ("google.la", true), 
		   						new ResultPair ("google.lb", true), 
		   						new ResultPair ("google.lc", true), 
		   						new ResultPair ("google.li", true), 
		   						new ResultPair ("google.lk", true), 
		   						new ResultPair ("google.lr", true), 
		   						new ResultPair ("google.ls", true), 
		   						new ResultPair ("google.lt", true), 
		   						new ResultPair ("google.lu", true), 
		   						new ResultPair ("google.lv", true), 
		   						new ResultPair ("google.ly", true), 
		   						new ResultPair ("google.ma", true), 
		   						new ResultPair ("google.mc", true), 
		   						new ResultPair ("google.md", true), 
		   						new ResultPair ("google.me", true), 
		   						new ResultPair ("google.mg", true), 
		   						new ResultPair ("google.mh", true), 
		   						new ResultPair ("google.mk", true), 
		   						new ResultPair ("google.ml", true), 
		   						new ResultPair ("google.mm", true), 
		   						new ResultPair ("google.mn", true), 
		   						new ResultPair ("google.mo", true), 
		   						new ResultPair ("google.mp", true), 
		   						new ResultPair ("google.mq", true), 
		   						new ResultPair ("google.mr", true), 
		   						new ResultPair ("google.ms", true), 
		   						new ResultPair ("google.mt", true), 
		   						new ResultPair ("google.mu", true), 
		   						new ResultPair ("google.mv", true), 
		   						new ResultPair ("google.mw", true), 
		   						new ResultPair ("google.mx", true), 
		   						new ResultPair ("google.my", true), 
		   						new ResultPair ("google.mz", true), 
		   						new ResultPair ("google.na", true), 
		   						new ResultPair ("google.nc", true), 
		   						new ResultPair ("google.ne", true), 
		   						new ResultPair ("google.nf", true), 
		   						new ResultPair ("google.ng", true), 
		   						new ResultPair ("google.ni", true),
		   						
		   						new ResultPair ("google.nf", true), 
		   						new ResultPair ("google.ng", true), 
		   						new ResultPair ("google.ni", true), 
		   						new ResultPair ("google.nl", true), 
		   						new ResultPair ("google.no", true), 
		   						new ResultPair ("google.np", true), 
		   						new ResultPair ("google.nr", true), 
		   						new ResultPair ("google.nu", true), 
		   						new ResultPair ("google.nz", true), 
		   						new ResultPair ("google.om", true), 
		   						new ResultPair ("google.pa", true), 
		   						new ResultPair ("google.pe", true), 
		   						new ResultPair ("google.pf", true), 
		   						new ResultPair ("google.pg", true), 
		   						new ResultPair ("google.ph", true), 
		   						new ResultPair ("google.pk", true), 
		   						new ResultPair ("google.pl", true), 
		   						new ResultPair ("google.pm", true), 
		   						new ResultPair ("google.pn", true), 
		   						new ResultPair ("google.pr", true), 
		   						new ResultPair ("google.ps", true), 
		   						new ResultPair ("google.pt", true), 
		   						new ResultPair ("google.pw", true), 
		   						new ResultPair ("google.py", true), 
		   						new ResultPair ("google.qa", true), 
		   						new ResultPair ("google.re", true), 
		   						new ResultPair ("google.ro", true), 
		   						new ResultPair ("google.rs", true), 
		   						new ResultPair ("google.ru", true), 
		   						new ResultPair ("google.rw", true), 
		   						new ResultPair ("google.sa", true), 
		   						new ResultPair ("google.sb", true), 
		   						new ResultPair ("google.sc", true), 
		   						new ResultPair ("google.sd", true), 
		   						new ResultPair ("google.se", true), 
		   						new ResultPair ("google.sg", true), 
		   						new ResultPair ("google.sh", true), 
		   						new ResultPair ("google.si", true), 
		   						new ResultPair ("google.sj", true), 
		   						new ResultPair ("google.sk", true), 
		   						new ResultPair ("google.sl", true), 
		   						new ResultPair ("google.sm", true), 
		   						new ResultPair ("google.sn", true), 
		   						new ResultPair ("google.so", true), 
		   						new ResultPair ("google.sr", true), 
		   						new ResultPair ("google.st", true), 
		   						new ResultPair ("google.su", true), 
		   						new ResultPair ("google.sv", true), 
		   						new ResultPair ("google.sy", true), 
		   						new ResultPair ("google.sz", true), 
		   						new ResultPair ("google.tc", true), 
		   						new ResultPair ("google.td", true), 
		   						new ResultPair ("google.tf", true), 
		   						new ResultPair ("google.tg", true),
		   						
		   						new ResultPair ("google.nl", true), 
		   						new ResultPair ("google.no", true), 
		   						new ResultPair ("google.np", true), 
		   						new ResultPair ("google.nr", true), 
		   						new ResultPair ("google.nu", true), 
		   						new ResultPair ("google.nz", true), 
		   						new ResultPair ("google.om", true), 
		   						new ResultPair ("google.pa", true), 
		   						new ResultPair ("google.pe", true), 
		   						new ResultPair ("google.pf", true), 
		   						new ResultPair ("google.pg", true), 
		   						new ResultPair ("google.ph", true), 
		   						new ResultPair ("google.pk", true), 
		   						new ResultPair ("google.pl", true), 
		   						new ResultPair ("google.pm", true), 
		   						new ResultPair ("google.pn", true), 
		   						new ResultPair ("google.pr", true), 
		   						new ResultPair ("google.ps", true), 
		   						new ResultPair ("google.pt", true), 
		   						new ResultPair ("google.pw", true), 
		   						new ResultPair ("google.py", true), 
		   						new ResultPair ("google.qa", true), 
		   						new ResultPair ("google.re", true), 
		   						new ResultPair ("google.ro", true), 
		   						new ResultPair ("google.rs", true), 
		   						new ResultPair ("google.ru", true), 
		   						new ResultPair ("google.rw", true), 
		   						new ResultPair ("google.sa", true), 
		   						new ResultPair ("google.sb", true), 
		   						new ResultPair ("google.sc", true), 
		   						new ResultPair ("google.sd", true), 
		   						new ResultPair ("google.se", true), 
		   						new ResultPair ("google.sg", true), 
		   						new ResultPair ("google.sh", true), 
		   						new ResultPair ("google.si", true), 
		   						new ResultPair ("google.sj", true), 
		   						new ResultPair ("google.sk", true), 
		   						new ResultPair ("google.sl", true), 
		   						new ResultPair ("google.sm", true), 
		   						new ResultPair ("google.sn", true), 
		   						new ResultPair ("google.so", true), 
		   						new ResultPair ("google.sr", true), 
		   						new ResultPair ("google.st", true), 
		   						new ResultPair ("google.su", true), 
		   						new ResultPair ("google.sv", true), 
		   						new ResultPair ("google.sy", true), 
		   						new ResultPair ("google.sz", true), 
		   						new ResultPair ("google.tc", true), 
		   						new ResultPair ("google.td", true), 
		   						new ResultPair ("google.tf", true), 
		   						new ResultPair ("google.tg", true), 
		   						new ResultPair ("google.th", true), 
		   						new ResultPair ("google.tj", true), 
		   						new ResultPair ("google.tk", true),
		   						
		   						new ResultPair ("google.tl", true), 
		   						new ResultPair ("google.tm", true), 
		   						new ResultPair ("google.tn", true), 
		   						new ResultPair ("google.to", true), 
		   						new ResultPair ("google.tp", true), 
		   						new ResultPair ("google.tr", true), 
		   						new ResultPair ("google.tt", true), 
		   						new ResultPair ("google.tv", true), 
		   						new ResultPair ("google.tw", true), 
		   						new ResultPair ("google.tz", true), 
		   						new ResultPair ("google.ua", true), 
		   						new ResultPair ("google.ug", true), 
		   						new ResultPair ("google.uk", true), 
		   						new ResultPair ("google.um", true), 
		   						new ResultPair ("google.us", true), 
		   						new ResultPair ("google.uy", true), 
		   						new ResultPair ("google.uz", true), 
		   						new ResultPair ("google.va", true), 
		   						new ResultPair ("google.vc", true), 
		   						new ResultPair ("google.ve", true), 
		   						new ResultPair ("google.vg", true), 
		   						new ResultPair ("google.vi", true), 
		   						new ResultPair ("google.vn", true), 
		   						new ResultPair ("google.vu", true), 
		   						new ResultPair ("google.wf", true), 
		   						new ResultPair ("google.ws", true), 
		   						new ResultPair ("google.ye", true), 
		   						new ResultPair ("google.yt", true), 
		   						new ResultPair ("google.yu", true), 
		   						new ResultPair ("google.za", true), 
		   						new ResultPair ("google.zm", true), 
		   						new ResultPair ("google.zw", true),
		   						
		   						new ResultPair("", false),
		   					};

   ResultPair[] port = {	new ResultPair(":", false),
							new ResultPair(":-1", false),
							new ResultPair(":0", true),
							new ResultPair(":1", true),
							new ResultPair(":10", true),
							new ResultPair(":100", true),
							new ResultPair(":1000", true),
							new ResultPair(":10000", true),
							new ResultPair(":100000", false),
							new ResultPair(":65535", true),
							new ResultPair(":65536", false),
							new ResultPair("", true),   
   							};
   
   ResultPair[] path = {	new ResultPair("/file", true),
		   					new ResultPair("/%20", true),
		   					new ResultPair("/file1/file2", true),
		   					new ResultPair("/", true),
		   					new ResultPair("//file", false),
		   					new ResultPair("//", false),		   					
		   					new ResultPair("/ /", false),
		   					new ResultPair("", true),	   					
		   					};
   
   ResultPair[] query = {	new ResultPair("?key=value", true),
		   					new ResultPair("?key1=value&key2=value", true),		   							   					
		   					new ResultPair("?key= value &", false),
		   					new ResultPair("", true),
   							};
   
}
