<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html><head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>13.3.&nbsp;Introducing romantest.py</title>
<link rel="stylesheet" href="13.3.%C2%A0Introducing%20romantest_files/diveintopython.css" type="text/css">
<link rev="made" href="http://www.diveintopython.net/unit_testing/josh@servercobra.com">
<meta name="generator" content="DocBook XSL Stylesheets V1.52.2">
<meta name="keywords" content="Python, Dive Into Python, tutorial, object-oriented, programming, documentation, book, free">
<meta name="description" content="Python from novice to pro">
<link rel="home" href="http://www.diveintopython.net/" title="Dive Into Python">
<link rel="up" href="http://www.diveintopython.net/" title="Chapter&nbsp;13.&nbsp;Unit Testing">
<link rel="previous" href="http://www.diveintopython.net/" title="13.2.&nbsp;Diving in">
<link rel="next" href="http://www.diveintopython.net/" title="13.4.&nbsp;Testing for success">
<script src="13.3.%C2%A0Introducing%20romantest_files/ca-pub-1879314568120827.js"></script><script src="13.3.%C2%A0Introducing%20romantest_files/ga.js" async="" type="text/javascript"></script><script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-9740779-18']);
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script></head>
<body>
<style type="text/css">body{margin-top:0!important;padding-top:0!important;min-width:800px!important;}#wm-ipp a:hover{text-decoration:underline!important;}</style>
<table id="Header" summary="" cellpadding="0" cellspacing="0" border="0" width="100%">
<tbody><tr>
<td id="breadcrumb" colspan="5" align="left" valign="top">You are here: <a href="http://www.diveintopython.net/index.html">Home</a>&nbsp;&gt;&nbsp;<a href="http://www.diveintopython.net/toc/index.html">Dive Into Python</a>&nbsp;&gt;&nbsp;<a href="http://www.diveintopython.net/unit_testing/index.html">Unit Testing</a>&nbsp;&gt;&nbsp;<span class="thispage">Introducing romantest.py</span></td>
<td id="navigation" align="right" valign="top">&nbsp;&nbsp;&nbsp;<a href="http://www.diveintopython.net/unit_testing/diving_in.html" title="Prev: “Diving in”">&lt;&lt;</a>&nbsp;&nbsp;&nbsp;<a href="http://www.diveintopython.net/unit_testing/testing_for_success.html" title="Next: “Testing for success”">&gt;&gt;</a></td>
</tr>
<tr>

<td colspan="2" id="logocontainer">
<p style="float:left; margin:0 10px 1em 0"><a href="http://www.amazon.com/gp/product/1475198116/ref=as_li_tf_il?ie=UTF8&amp;tag=serve01-20&amp;linkCode=as2&amp;camp=1789&amp;creative=9325&amp;creativeASIN=1475198116"><img src="13.3.%C2%A0Introducing%20romantest_files/q.asc" border="0"></a><img src="13.3.%C2%A0Introducing%20romantest_files/ir.gif" alt="" style="border:none !important; margin:0px !important;" border="0" height="1" width="1"></p>


<h1 id="logo"><a href="http://www.diveintopython.net/index.html" accesskey="1">Dive Into Python</a></h1>
<p id="tagline">Python from novice to pro</p>
<img src="13.3.%C2%A0Introducing%20romantest_files/amazon-buy-button.gif">
</td>
<td colspan="3" align="center">
<script type="text/javascript"><!--
google_ad_client = "ca-pub-1879314568120827";
/* DiveIntoPython */
google_ad_slot = "8002881514";
google_ad_width = 468;
google_ad_height = 60;
//-->
</script>
<script type="text/javascript" src="13.3.%C2%A0Introducing%20romantest_files/show_ads.js">
</script><ins id="aswift_0_expand" style="display:inline-table;border:none;height:60px;margin:0;padding:0;position:relative;visibility:visible;width:468px;background-color:transparent"><ins id="aswift_0_anchor" style="display:block;border:none;height:60px;margin:0;padding:0;position:relative;visibility:visible;width:468px;background-color:transparent"><iframe marginwidth="0" marginheight="0" vspace="0" hspace="0" allowtransparency="true" allowfullscreen="true" onload="var i=this.id,s=window.google_iframe_oncopy,H=s&amp;&amp;s.handlers,h=H&amp;&amp;H[i],w=this.contentWindow,d;try{d=w.document}catch(e){}if(h&amp;&amp;d&amp;&amp;(!d.body||!d.body.firstChild)){if(h.call){setTimeout(h,0)}else if(h.match){try{h=s.upd(h,i)}catch(e){}w.location.replace(h)}}" id="aswift_0" name="aswift_0" style="left:0;position:absolute;top:0;" frameborder="0" height="60" scrolling="no" width="468"></iframe></ins></ins>
</td>
<td colspan="3" align="right">
<form id="search" method="GET" action="http://www.google.com/custom">
<p><label for="q" accesskey="4">Find:&nbsp;</label><input id="q" name="q" size="20" maxlength="255" value=" " type="text"> <input value="Search" type="submit"><input name="cof" value="LW:752;L:http://diveintopython.org/images/diveintopython.png;LH:42;AH:left;GL:0;AWFID:3ced2bb1f7f1b212;" type="hidden"><input name="domains" value="diveintopython.org" type="hidden"><input name="sitesearch" value="diveintopython.org" type="hidden"></p>
</form>
<p><a href="https://github.com/pcsforeducation/diveintopython/issues?sort=created&amp;state=open">Report issues<img style="margin-left:10px" src="13.3.%C2%A0Introducing%20romantest_files/logo_github.png" height="40"></a></p>
</td>
</tr>
</tbody></table>
<div class="section" lang="en">
<div class="titlepage">
<div>
<div>
<h2 class="title"><a name="roman.romantest"></a>13.3.&nbsp;Introducing <tt class="filename">romantest.py</tt></h2>
</div>
</div>
<div></div>
</div>
<div class="abstract">
<p>This is the complete test suite for your Roman numeral conversion functions, which are yet to be written but will eventually
               be in <tt class="filename">roman.py</tt>.  It is not immediately obvious how it all fits together; none of these classes or methods reference any of the others. 
               There are good reasons for this, as you'll see shortly.
            </p>
</div>
<div class="example"><a name="d0e32173"></a><h3 class="title">Example&nbsp;13.1.&nbsp;<tt class="filename">romantest.py</tt></h3>
<p>If you have not already done so, you can <a href="http://www.diveintopython.net/download/diveintopython-examples-5.4.zip" title="Download example scripts">download this and other examples</a> used in this book.
            </p><pre class="programlisting"><span class="pystring">"""Unit test for roman.py"""</span>

<span class="pykeyword">import</span> roman
<span class="pykeyword">import</span> unittest

<span class="pykeyword">class</span><span class="pyclass"> KnownValues</span>(unittest.TestCase):                          
    knownValues = ( (1, <span class="pystring">'I'</span>),
                    (2, <span class="pystring">'II'</span>),
                    (3, <span class="pystring">'III'</span>),
                    (4, <span class="pystring">'IV'</span>),
                    (5, <span class="pystring">'V'</span>),
                    (6, <span class="pystring">'VI'</span>),
                    (7, <span class="pystring">'VII'</span>),
                    (8, <span class="pystring">'VIII'</span>),
                    (9, <span class="pystring">'IX'</span>),
                    (10, <span class="pystring">'X'</span>),
                    (50, <span class="pystring">'L'</span>),
                    (100, <span class="pystring">'C'</span>),
                    (500, <span class="pystring">'D'</span>),
                    (1000, <span class="pystring">'M'</span>),
                    (31, <span class="pystring">'XXXI'</span>),
                    (148, <span class="pystring">'CXLVIII'</span>),
                    (294, <span class="pystring">'CCXCIV'</span>),
                    (312, <span class="pystring">'CCCXII'</span>),
                    (421, <span class="pystring">'CDXXI'</span>),
                    (528, <span class="pystring">'DXXVIII'</span>),
                    (621, <span class="pystring">'DCXXI'</span>),
                    (782, <span class="pystring">'DCCLXXXII'</span>),
                    (870, <span class="pystring">'DCCCLXX'</span>),
                    (941, <span class="pystring">'CMXLI'</span>),
                    (1043, <span class="pystring">'MXLIII'</span>),
                    (1110, <span class="pystring">'MCX'</span>),
                    (1226, <span class="pystring">'MCCXXVI'</span>),
                    (1301, <span class="pystring">'MCCCI'</span>),
                    (1485, <span class="pystring">'MCDLXXXV'</span>),
                    (1509, <span class="pystring">'MDIX'</span>),
                    (1607, <span class="pystring">'MDCVII'</span>),
                    (1754, <span class="pystring">'MDCCLIV'</span>),
                    (1832, <span class="pystring">'MDCCCXXXII'</span>),
                    (1993, <span class="pystring">'MCMXCIII'</span>),
                    (2074, <span class="pystring">'MMLXXIV'</span>),
                    (2152, <span class="pystring">'MMCLII'</span>),
                    (2212, <span class="pystring">'MMCCXII'</span>),
                    (2343, <span class="pystring">'MMCCCXLIII'</span>),
                    (2499, <span class="pystring">'MMCDXCIX'</span>),
                    (2574, <span class="pystring">'MMDLXXIV'</span>),
                    (2646, <span class="pystring">'MMDCXLVI'</span>),
                    (2723, <span class="pystring">'MMDCCXXIII'</span>),
                    (2892, <span class="pystring">'MMDCCCXCII'</span>),
                    (2975, <span class="pystring">'MMCMLXXV'</span>),
                    (3051, <span class="pystring">'MMMLI'</span>),
                    (3185, <span class="pystring">'MMMCLXXXV'</span>),
                    (3250, <span class="pystring">'MMMCCL'</span>),
                    (3313, <span class="pystring">'MMMCCCXIII'</span>),
                    (3408, <span class="pystring">'MMMCDVIII'</span>),
                    (3501, <span class="pystring">'MMMDI'</span>),
                    (3610, <span class="pystring">'MMMDCX'</span>),
                    (3743, <span class="pystring">'MMMDCCXLIII'</span>),
                    (3844, <span class="pystring">'MMMDCCCXLIV'</span>),
                    (3888, <span class="pystring">'MMMDCCCLXXXVIII'</span>),
                    (3940, <span class="pystring">'MMMCMXL'</span>),
                    (3999, <span class="pystring">'MMMCMXCIX'</span>))                       

    <span class="pykeyword">def</span><span class="pyclass"> testToRomanKnownValues</span>(self):                          
        <span class="pystring">"""toRoman should give known result with known input"""</span>
        <span class="pykeyword">for</span> integer, numeral <span class="pykeyword">in</span> self.knownValues:              
            result = roman.toRoman(integer)                    
            self.assertEqual(numeral, result)                  

    <span class="pykeyword">def</span><span class="pyclass"> testFromRomanKnownValues</span>(self):                          
        <span class="pystring">"""fromRoman should give known result with known input"""</span>
        <span class="pykeyword">for</span> integer, numeral <span class="pykeyword">in</span> self.knownValues:                
            result = roman.fromRoman(numeral)                    
            self.assertEqual(integer, result)                    

<span class="pykeyword">class</span><span class="pyclass"> ToRomanBadInput</span>(unittest.TestCase):                            
    <span class="pykeyword">def</span><span class="pyclass"> testTooLarge</span>(self):                                          
        <span class="pystring">"""toRoman should fail with large input"""</span>                   
        self.assertRaises(roman.OutOfRangeError, roman.toRoman, 4000)

    <span class="pykeyword">def</span><span class="pyclass"> testZero</span>(self):                                              
        <span class="pystring">"""toRoman should fail with 0 input"""</span>                       
        self.assertRaises(roman.OutOfRangeError, roman.toRoman, 0)   

    <span class="pykeyword">def</span><span class="pyclass"> testNegative</span>(self):                                          
        <span class="pystring">"""toRoman should fail with negative input"""</span>                
        self.assertRaises(roman.OutOfRangeError, roman.toRoman, -1)  

    <span class="pykeyword">def</span><span class="pyclass"> testNonInteger</span>(self):                                        
        <span class="pystring">"""toRoman should fail with non-integer input"""</span>             
        self.assertRaises(roman.NotIntegerError, roman.toRoman, 0.5) 

<span class="pykeyword">class</span><span class="pyclass"> FromRomanBadInput</span>(unittest.TestCase):                                      
    <span class="pykeyword">def</span><span class="pyclass"> testTooManyRepeatedNumerals</span>(self):                                       
        <span class="pystring">"""fromRoman should fail with too many repeated numerals"""</span>              
        <span class="pykeyword">for</span> s <span class="pykeyword">in</span> (<span class="pystring">'MMMM'</span>, <span class="pystring">'DD'</span>, <span class="pystring">'CCCC'</span>, <span class="pystring">'LL'</span>, <span class="pystring">'XXXX'</span>, <span class="pystring">'VV'</span>, <span class="pystring">'IIII'</span>):             
            self.assertRaises(roman.InvalidRomanNumeralError, roman.fromRoman, s)

    <span class="pykeyword">def</span><span class="pyclass"> testRepeatedPairs</span>(self):                                                 
        <span class="pystring">"""fromRoman should fail with repeated pairs of numerals"""</span>              
        <span class="pykeyword">for</span> s <span class="pykeyword">in</span> (<span class="pystring">'CMCM'</span>, <span class="pystring">'CDCD'</span>, <span class="pystring">'XCXC'</span>, <span class="pystring">'XLXL'</span>, <span class="pystring">'IXIX'</span>, <span class="pystring">'IVIV'</span>):               
            self.assertRaises(roman.InvalidRomanNumeralError, roman.fromRoman, s)

    <span class="pykeyword">def</span><span class="pyclass"> testMalformedAntecedent</span>(self):                                           
        <span class="pystring">"""fromRoman should fail with malformed antecedents"""</span>                   
        <span class="pykeyword">for</span> s <span class="pykeyword">in</span> (<span class="pystring">'IIMXCC'</span>, <span class="pystring">'VX'</span>, <span class="pystring">'DCM'</span>, <span class="pystring">'CMM'</span>, <span class="pystring">'IXIV'</span>,
                  <span class="pystring">'MCMC'</span>, <span class="pystring">'XCX'</span>, <span class="pystring">'IVI'</span>, <span class="pystring">'LM'</span>, <span class="pystring">'LD'</span>, <span class="pystring">'LC'</span>):                       
            self.assertRaises(roman.InvalidRomanNumeralError, roman.fromRoman, s)

<span class="pykeyword">class</span><span class="pyclass"> SanityCheck</span>(unittest.TestCase):        
    <span class="pykeyword">def</span><span class="pyclass"> testSanity</span>(self):                    
        <span class="pystring">"""fromRoman(toRoman(n))==n for all n"""</span>
        <span class="pykeyword">for</span> integer <span class="pykeyword">in</span> range(1, 4000):       
            numeral = roman.toRoman(integer) 
            result = roman.fromRoman(numeral)
            self.assertEqual(integer, result)

<span class="pykeyword">class</span><span class="pyclass"> CaseCheck</span>(unittest.TestCase):                   
    <span class="pykeyword">def</span><span class="pyclass"> testToRomanCase</span>(self):                        
        <span class="pystring">"""toRoman should always return uppercase"""</span>  
        <span class="pykeyword">for</span> integer <span class="pykeyword">in</span> range(1, 4000):                
            numeral = roman.toRoman(integer)          
            self.assertEqual(numeral, numeral.upper())

    <span class="pykeyword">def</span><span class="pyclass"> testFromRomanCase</span>(self):                      
        <span class="pystring">"""fromRoman should only accept uppercase input"""</span>
        <span class="pykeyword">for</span> integer <span class="pykeyword">in</span> range(1, 4000):                
            numeral = roman.toRoman(integer)          
            roman.fromRoman(numeral.upper())          
            self.assertRaises(roman.InvalidRomanNumeralError,
                              roman.fromRoman, numeral.lower())

<span class="pykeyword">if</span> __name__ == <span class="pystring">"__main__"</span>:
    unittest.main()   </pre></div>
<div class="furtherreading">
<h3>Further reading</h3>
<ul>
<li><a href="http://www.diveintopython.net/">The <span class="application">PyUnit</span> home page</a> has an in-depth discussion of <a href="http://www.diveintopython.net/pyunit.html">using the <tt class="filename">unittest</tt> framework</a>, including advanced features not covered in this chapter.
               </li>
<li><a href="http://www.diveintopython.net/pyunit.html">The <span class="application">PyUnit</span> <span class="acronym">FAQ</span></a> explains <a href="http://www.diveintopython.net/pyunit.html#WHERE">why test cases are stored separately</a> from the code they test.
               </li>
<li><a href="http://www.diveintopython.net/doc/current/lib/"><i class="citetitle"><span class="application">Python</span> Library Reference</i></a> summarizes the <a href="http://www.diveintopython.net/doc/current/lib/module-unittest.html"><tt class="filename">unittest</tt></a> module.
               </li>
<li><a href="http://www.diveintopython.net/">ExtremeProgramming.org</a> discusses <a href="http://www.diveintopython.net/rules/unittests.html">why you should write unit tests</a>.
               </li>
<li><a href="http://www.diveintopython.net/cgi/wiki">The Portland Pattern Repository</a> has an ongoing discussion of <a href="http://www.diveintopython.net/cgi/wiki?UnitTests">unit tests</a>, including a <a href="http://www.diveintopython.net/cgi/wiki?StandardDefinitionOfUnitTest">standard definition</a>, why you should <a href="http://www.diveintopython.net/cgi/wiki?CodeUnitTestFirst">code unit tests first</a>, and several in-depth <a href="http://www.diveintopython.net/cgi/wiki?UnitTestTrial">case studies</a>.
               </li>
</ul>
</div>
</div>
<table class="Footer" summary="" cellpadding="0" cellspacing="0" border="0" width="100%">
<tbody><tr>
<td align="left" width="35%"><br><a class="NavigationArrow" href="http://www.diveintopython.net/unit_testing/diving_in.html">&lt;&lt;&nbsp;Diving in</a></td>
<td align="center" width="30%"><br>&nbsp;<span class="divider">|</span>&nbsp;<a href="http://www.diveintopython.net/unit_testing/index.html#roman.intro" title="13.1.&nbsp;Introduction to Roman numerals">1</a> <span class="divider">|</span> <a href="http://www.diveintopython.net/unit_testing/diving_in.html" title="13.2.&nbsp;Diving in">2</a> <span class="divider">|</span> <span class="thispage">3</span> <span class="divider">|</span> <a href="http://www.diveintopython.net/unit_testing/testing_for_success.html" title="13.4.&nbsp;Testing for success">4</a> <span class="divider">|</span> <a href="http://www.diveintopython.net/unit_testing/testing_for_failure.html" title="13.5.&nbsp;Testing for failure">5</a> <span class="divider">|</span> <a href="http://www.diveintopython.net/unit_testing/testing_for_sanity.html" title="13.6.&nbsp;Testing for sanity">6</a>&nbsp;<span class="divider">|</span>&nbsp;
            </td>
<td align="right" width="35%"><br><a class="NavigationArrow" href="http://www.diveintopython.net/unit_testing/testing_for_success.html">Testing for success&nbsp;&gt;&gt;</a></td>
</tr>
<tr>
<td colspan="3"><br></td>
</tr>
</tbody></table>
<div class="Footer">
<script type="text/javascript"><!--
google_ad_client = "ca-pub-1879314568120827";
/* DiveIntoPython */
google_ad_slot = "8002881514";
google_ad_width = 468;
google_ad_height = 60;
//-->
</script>
<script type="text/javascript" src="13.3.%C2%A0Introducing%20romantest_files/show_ads.js">
</script><ins id="aswift_1_expand" style="display:inline-table;border:none;height:60px;margin:0;padding:0;position:relative;visibility:visible;width:468px;background-color:transparent"><ins id="aswift_1_anchor" style="display:block;border:none;height:60px;margin:0;padding:0;position:relative;visibility:visible;width:468px;background-color:transparent"><iframe marginwidth="0" marginheight="0" vspace="0" hspace="0" allowtransparency="true" allowfullscreen="true" onload="var i=this.id,s=window.google_iframe_oncopy,H=s&amp;&amp;s.handlers,h=H&amp;&amp;H[i],w=this.contentWindow,d;try{d=w.document}catch(e){}if(h&amp;&amp;d&amp;&amp;(!d.body||!d.body.firstChild)){if(h.call){setTimeout(h,0)}else if(h.match){try{h=s.upd(h,i)}catch(e){}w.location.replace(h)}}" id="aswift_1" name="aswift_1" style="left:0;position:absolute;top:0;" frameborder="0" height="60" scrolling="no" width="468"></iframe></ins></ins>
<p><a href="https://github.com/pcsforeducation/diveintopython/issues?sort=created&amp;state=open">Report issues<img style="margin-left:10px" src="13.3.%C2%A0Introducing%20romantest_files/logo_github.png" height="40"></a></p>
<p class="copyright">Copyright © 2000, 2001, 2002, 2003, 2004 <a href="mailto:josh@servercobra.com">Mark Pilgrim</a></p>
</div>

</body></html>