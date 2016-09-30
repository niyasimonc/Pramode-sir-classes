<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en"><!-- ViewVC :: http://www.viewvc.org/ --><head>
<meta http-equiv="content-type" content="text/html; charset=UTF-8">
<title>[projects] Contents of /python/trunk/Python/marshal.c</title>
<meta name="generator" content="ViewVC 1.1.5">
<link rel="shortcut icon" href="http://svn.python.org/viewvc/images/favicon.ico" type="image/x-icon">
<link rel="stylesheet" href="%5Bprojects%5D%20Contents%20of%20_python_trunk_Python_marshal_files/styles.css" type="text/css">

</head>
<body>
<div class="vc_navheader">
<table><tbody><tr>
<td><strong><a href="http://svn.python.org/view?view=roots"><span class="pathdiv">/</span></a><a href="http://svn.python.org/view/">[projects]</a><span class="pathdiv">/</span><a href="http://svn.python.org/view/python/">python</a><span class="pathdiv">/</span><a href="http://svn.python.org/view/python/trunk/">trunk</a><span class="pathdiv">/</span><a href="http://svn.python.org/view/python/trunk/Python/">Python</a><span class="pathdiv">/</span><a href="http://svn.python.org/view/python/trunk/Python/marshal.c?view=log">marshal.c</a></strong></td>
<td style="text-align: right;"></td>
</tr></tbody></table>
</div>
<div style="float: right; padding: 5px;"><a href="http://www.viewvc.org/" title="ViewVC Home"><img src="%5Bprojects%5D%20Contents%20of%20_python_trunk_Python_marshal_files/viewvc-logo.png" alt="ViewVC logotype" height="70" width="240"></a></div>
<h1>Contents of /python/trunk/Python/marshal.c</h1>

<p style="margin:0;">

<a href="http://svn.python.org/view/python/trunk/Python/"><img src="%5Bprojects%5D%20Contents%20of%20_python_trunk_Python_marshal_files/back_small.png" class="vc_icon" alt="Parent Directory"> Parent Directory</a>

| <a href="http://svn.python.org/view/python/trunk/Python/marshal.c?view=log"><img src="%5Bprojects%5D%20Contents%20of%20_python_trunk_Python_marshal_files/log.png" class="vc_icon" alt="Revision Log"> Revision Log</a>




</p>

<hr>
<div class="vc_summary">
Revision <a href="http://svn.python.org/view?view=revision&amp;revision=81029"><strong>81029</strong></a> -
(<a href="http://svn.python.org/view/python/trunk/Python/marshal.c?annotate=81029"><strong>show annotations</strong></a>)
(<a href="http://svn.python.org/view/*checkout*/python/trunk/Python/marshal.c?revision=81029"><strong>download</strong></a>)
(<a href="http://svn.python.org/view/*checkout*/python/trunk/Python/marshal.c?revision=81029&amp;content-type=text%2Fplain"><strong>as text</strong></a>)

<br><em>Sun May  9 14:46:46 2010 UTC</em>
(5 years, 4 months ago)
by <em>antoine.pitrou</em>






<br>File MIME type: text/x-csrc


<br>File size: 39309 byte(s)






<pre class="vc_log">Untabify C files. Will watch buildbots.

</pre>

</div>






<div id="vc_file">
<table cellpadding="0" cellspacing="0">








<tbody><tr class="vc_row_odd" id="l1">
<td class="vc_file_line_number">1</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l2">
<td class="vc_file_line_number">2</td>

<td class="vc_file_line_text"><span class="pygments-cm">/* Write Python objects to files and read them back.</span>
</td>
</tr>




<tr class="vc_row_odd" id="l3">
<td class="vc_file_line_number">3</td>

<td class="vc_file_line_text"><span class="pygments-cm">   This is intended for writing and reading compiled Python code only;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l4">
<td class="vc_file_line_number">4</td>

<td class="vc_file_line_text"><span class="pygments-cm">   a true persistent storage facility would be much harder, since</span>
</td>
</tr>




<tr class="vc_row_odd" id="l5">
<td class="vc_file_line_number">5</td>

<td class="vc_file_line_text"><span class="pygments-cm">   it would have to take circular links and sharing into account. */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l6">
<td class="vc_file_line_number">6</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l7">
<td class="vc_file_line_number">7</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define PY_SSIZE_T_CLEAN</span>
</td>
</tr>




<tr class="vc_row_odd" id="l8">
<td class="vc_file_line_number">8</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l9">
<td class="vc_file_line_number">9</td>

<td class="vc_file_line_text"><span class="pygments-cp">#include "Python.h"</span>
</td>
</tr>




<tr class="vc_row_odd" id="l10">
<td class="vc_file_line_number">10</td>

<td class="vc_file_line_text"><span class="pygments-cp">#include "longintrepr.h"</span>
</td>
</tr>




<tr class="vc_row_odd" id="l11">
<td class="vc_file_line_number">11</td>

<td class="vc_file_line_text"><span class="pygments-cp">#include "code.h"</span>
</td>
</tr>




<tr class="vc_row_odd" id="l12">
<td class="vc_file_line_number">12</td>

<td class="vc_file_line_text"><span class="pygments-cp">#include "marshal.h"</span>
</td>
</tr>




<tr class="vc_row_odd" id="l13">
<td class="vc_file_line_number">13</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l14">
<td class="vc_file_line_number">14</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define ABS(x) ((x) &lt; 0 ? -(x) : (x))</span>
</td>
</tr>




<tr class="vc_row_odd" id="l15">
<td class="vc_file_line_number">15</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l16">
<td class="vc_file_line_number">16</td>

<td class="vc_file_line_text"><span class="pygments-cm">/* High water mark to determine when the marshalled object is dangerously deep</span>
</td>
</tr>




<tr class="vc_row_odd" id="l17">
<td class="vc_file_line_number">17</td>

<td class="vc_file_line_text"><span class="pygments-cm"> * and risks coring the interpreter.  When the object stack gets this deep,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l18">
<td class="vc_file_line_number">18</td>

<td class="vc_file_line_text"><span class="pygments-cm"> * raise an exception instead of continuing.</span>
</td>
</tr>




<tr class="vc_row_odd" id="l19">
<td class="vc_file_line_number">19</td>

<td class="vc_file_line_text"><span class="pygments-cm"> */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l20">
<td class="vc_file_line_number">20</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define MAX_MARSHAL_STACK_DEPTH 2000</span>
</td>
</tr>




<tr class="vc_row_odd" id="l21">
<td class="vc_file_line_number">21</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l22">
<td class="vc_file_line_number">22</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_NULL               '0'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l23">
<td class="vc_file_line_number">23</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_NONE               'N'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l24">
<td class="vc_file_line_number">24</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_FALSE              'F'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l25">
<td class="vc_file_line_number">25</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_TRUE               'T'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l26">
<td class="vc_file_line_number">26</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_STOPITER           'S'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l27">
<td class="vc_file_line_number">27</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_ELLIPSIS           '.'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l28">
<td class="vc_file_line_number">28</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_INT                'i'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l29">
<td class="vc_file_line_number">29</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_INT64              'I'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l30">
<td class="vc_file_line_number">30</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_FLOAT              'f'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l31">
<td class="vc_file_line_number">31</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_BINARY_FLOAT       'g'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l32">
<td class="vc_file_line_number">32</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_COMPLEX            'x'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l33">
<td class="vc_file_line_number">33</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_BINARY_COMPLEX     'y'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l34">
<td class="vc_file_line_number">34</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_LONG               'l'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l35">
<td class="vc_file_line_number">35</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_STRING             's'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l36">
<td class="vc_file_line_number">36</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_INTERNED           't'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l37">
<td class="vc_file_line_number">37</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_STRINGREF          'R'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l38">
<td class="vc_file_line_number">38</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_TUPLE              '('</span>
</td>
</tr>




<tr class="vc_row_odd" id="l39">
<td class="vc_file_line_number">39</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_LIST               '['</span>
</td>
</tr>




<tr class="vc_row_odd" id="l40">
<td class="vc_file_line_number">40</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_DICT               '{'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l41">
<td class="vc_file_line_number">41</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_CODE               'c'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l42">
<td class="vc_file_line_number">42</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_UNICODE            'u'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l43">
<td class="vc_file_line_number">43</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_UNKNOWN            '?'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l44">
<td class="vc_file_line_number">44</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_SET                '&lt;'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l45">
<td class="vc_file_line_number">45</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define TYPE_FROZENSET          '&gt;'</span>
</td>
</tr>




<tr class="vc_row_odd" id="l46">
<td class="vc_file_line_number">46</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l47">
<td class="vc_file_line_number">47</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define WFERR_OK 0</span>
</td>
</tr>




<tr class="vc_row_odd" id="l48">
<td class="vc_file_line_number">48</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define WFERR_UNMARSHALLABLE 1</span>
</td>
</tr>




<tr class="vc_row_odd" id="l49">
<td class="vc_file_line_number">49</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define WFERR_NESTEDTOODEEP 2</span>
</td>
</tr>




<tr class="vc_row_odd" id="l50">
<td class="vc_file_line_number">50</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define WFERR_NOMEMORY 3</span>
</td>
</tr>




<tr class="vc_row_odd" id="l51">
<td class="vc_file_line_number">51</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l52">
<td class="vc_file_line_number">52</td>

<td class="vc_file_line_text"><span class="pygments-k">typedef</span> <span class="pygments-k">struct</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l53">
<td class="vc_file_line_number">53</td>

<td class="vc_file_line_text">    <span class="pygments-kt">FILE</span> <span class="pygments-o">*</span><span class="pygments-n">fp</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l54">
<td class="vc_file_line_number">54</td>

<td class="vc_file_line_text">    <span class="pygments-kt">int</span> <span class="pygments-n">error</span><span class="pygments-p">;</span>  <span class="pygments-cm">/* see WFERR_* values */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l55">
<td class="vc_file_line_number">55</td>

<td class="vc_file_line_text">    <span class="pygments-kt">int</span> <span class="pygments-n">depth</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l56">
<td class="vc_file_line_number">56</td>

<td class="vc_file_line_text">    <span class="pygments-cm">/* If fp == NULL, the following are valid: */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l57">
<td class="vc_file_line_number">57</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">str</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l58">
<td class="vc_file_line_number">58</td>

<td class="vc_file_line_text">    <span class="pygments-kt">char</span> <span class="pygments-o">*</span><span class="pygments-n">ptr</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l59">
<td class="vc_file_line_number">59</td>

<td class="vc_file_line_text">    <span class="pygments-kt">char</span> <span class="pygments-o">*</span><span class="pygments-n">end</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l60">
<td class="vc_file_line_number">60</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">strings</span><span class="pygments-p">;</span> <span class="pygments-cm">/* dict on marshal, list on unmarshal */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l61">
<td class="vc_file_line_number">61</td>

<td class="vc_file_line_text">    <span class="pygments-kt">int</span> <span class="pygments-n">version</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l62">
<td class="vc_file_line_number">62</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span> <span class="pygments-n">WFILE</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l63">
<td class="vc_file_line_number">63</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l64">
<td class="vc_file_line_number">64</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define w_byte(c, p) if (((p)-&gt;fp)) putc((c), (p)-&gt;fp); \</span>
</td>
</tr>




<tr class="vc_row_odd" id="l65">
<td class="vc_file_line_number">65</td>

<td class="vc_file_line_text"><span class="pygments-cp">                      else if ((p)-&gt;ptr != (p)-&gt;end) *(p)-&gt;ptr++ = (c); \</span>
</td>
</tr>




<tr class="vc_row_odd" id="l66">
<td class="vc_file_line_number">66</td>

<td class="vc_file_line_text"><span class="pygments-cp">                           else w_more(c, p)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l67">
<td class="vc_file_line_number">67</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l68">
<td class="vc_file_line_number">68</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-kt">void</span>
</td>
</tr>




<tr class="vc_row_odd" id="l69">
<td class="vc_file_line_number">69</td>

<td class="vc_file_line_text"><span class="pygments-nf">w_more</span><span class="pygments-p">(</span><span class="pygments-kt">int</span> <span class="pygments-n">c</span><span class="pygments-p">,</span> <span class="pygments-n">WFILE</span> <span class="pygments-o">*</span><span class="pygments-n">p</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l70">
<td class="vc_file_line_number">70</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l71">
<td class="vc_file_line_number">71</td>

<td class="vc_file_line_text">    <span class="pygments-n">Py_ssize_t</span> <span class="pygments-n">size</span><span class="pygments-p">,</span> <span class="pygments-n">newsize</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l72">
<td class="vc_file_line_number">72</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">str</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l73">
<td class="vc_file_line_number">73</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span><span class="pygments-p">;</span> <span class="pygments-cm">/* An error already occurred */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l74">
<td class="vc_file_line_number">74</td>

<td class="vc_file_line_text">    <span class="pygments-n">size</span> <span class="pygments-o">=</span> <span class="pygments-n">PyString_Size</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">str</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l75">
<td class="vc_file_line_number">75</td>

<td class="vc_file_line_text">    <span class="pygments-n">newsize</span> <span class="pygments-o">=</span> <span class="pygments-n">size</span> <span class="pygments-o">+</span> <span class="pygments-n">size</span> <span class="pygments-o">+</span> <span class="pygments-mi">1024</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l76">
<td class="vc_file_line_number">76</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">newsize</span> <span class="pygments-o">&gt;</span> <span class="pygments-mi">32</span><span class="pygments-o">*</span><span class="pygments-mi">1024</span><span class="pygments-o">*</span><span class="pygments-mi">1024</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l77">
<td class="vc_file_line_number">77</td>

<td class="vc_file_line_text">        <span class="pygments-n">newsize</span> <span class="pygments-o">=</span> <span class="pygments-n">size</span> <span class="pygments-o">+</span> <span class="pygments-p">(</span><span class="pygments-n">size</span> <span class="pygments-o">&gt;&gt;</span> <span class="pygments-mi">3</span><span class="pygments-p">);</span>           <span class="pygments-cm">/* 12.5% overallocation */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l78">
<td class="vc_file_line_number">78</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l79">
<td class="vc_file_line_number">79</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">_PyString_Resize</span><span class="pygments-p">(</span><span class="pygments-o">&amp;</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">str</span><span class="pygments-p">,</span> <span class="pygments-n">newsize</span><span class="pygments-p">)</span> <span class="pygments-o">!=</span> <span class="pygments-mi">0</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l80">
<td class="vc_file_line_number">80</td>

<td class="vc_file_line_text">        <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">ptr</span> <span class="pygments-o">=</span> <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">end</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l81">
<td class="vc_file_line_number">81</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l82">
<td class="vc_file_line_number">82</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l83">
<td class="vc_file_line_number">83</td>

<td class="vc_file_line_text">        <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">ptr</span> <span class="pygments-o">=</span> <span class="pygments-n">PyString_AS_STRING</span><span class="pygments-p">((</span><span class="pygments-n">PyStringObject</span> <span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">str</span><span class="pygments-p">)</span> <span class="pygments-o">+</span> <span class="pygments-n">size</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l84">
<td class="vc_file_line_number">84</td>

<td class="vc_file_line_text">        <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">end</span> <span class="pygments-o">=</span>
</td>
</tr>




<tr class="vc_row_odd" id="l85">
<td class="vc_file_line_number">85</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyString_AS_STRING</span><span class="pygments-p">((</span><span class="pygments-n">PyStringObject</span> <span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">str</span><span class="pygments-p">)</span> <span class="pygments-o">+</span> <span class="pygments-n">newsize</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l86">
<td class="vc_file_line_number">86</td>

<td class="vc_file_line_text">        <span class="pygments-o">*</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">ptr</span><span class="pygments-o">++</span> <span class="pygments-o">=</span> <span class="pygments-n">Py_SAFE_DOWNCAST</span><span class="pygments-p">(</span><span class="pygments-n">c</span><span class="pygments-p">,</span> <span class="pygments-kt">int</span><span class="pygments-p">,</span> <span class="pygments-kt">char</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l87">
<td class="vc_file_line_number">87</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l88">
<td class="vc_file_line_number">88</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l89">
<td class="vc_file_line_number">89</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l90">
<td class="vc_file_line_number">90</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-kt">void</span>
</td>
</tr>




<tr class="vc_row_odd" id="l91">
<td class="vc_file_line_number">91</td>

<td class="vc_file_line_text"><span class="pygments-nf">w_string</span><span class="pygments-p">(</span><span class="pygments-kt">char</span> <span class="pygments-o">*</span><span class="pygments-n">s</span><span class="pygments-p">,</span> <span class="pygments-kt">int</span> <span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">WFILE</span> <span class="pygments-o">*</span><span class="pygments-n">p</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l92">
<td class="vc_file_line_number">92</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l93">
<td class="vc_file_line_number">93</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">fp</span> <span class="pygments-o">!=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l94">
<td class="vc_file_line_number">94</td>

<td class="vc_file_line_text">        <span class="pygments-n">fwrite</span><span class="pygments-p">(</span><span class="pygments-n">s</span><span class="pygments-p">,</span> <span class="pygments-mi">1</span><span class="pygments-p">,</span> <span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">fp</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l95">
<td class="vc_file_line_number">95</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l96">
<td class="vc_file_line_number">96</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l97">
<td class="vc_file_line_number">97</td>

<td class="vc_file_line_text">        <span class="pygments-k">while</span> <span class="pygments-p">(</span><span class="pygments-o">--</span><span class="pygments-n">n</span> <span class="pygments-o">&gt;=</span> <span class="pygments-mi">0</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l98">
<td class="vc_file_line_number">98</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-o">*</span><span class="pygments-n">s</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l99">
<td class="vc_file_line_number">99</td>

<td class="vc_file_line_text">            <span class="pygments-n">s</span><span class="pygments-o">++</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l100">
<td class="vc_file_line_number">100</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l101">
<td class="vc_file_line_number">101</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l102">
<td class="vc_file_line_number">102</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l103">
<td class="vc_file_line_number">103</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l104">
<td class="vc_file_line_number">104</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-kt">void</span>
</td>
</tr>




<tr class="vc_row_odd" id="l105">
<td class="vc_file_line_number">105</td>

<td class="vc_file_line_text"><span class="pygments-nf">w_short</span><span class="pygments-p">(</span><span class="pygments-kt">int</span> <span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-n">WFILE</span> <span class="pygments-o">*</span><span class="pygments-n">p</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l106">
<td class="vc_file_line_number">106</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l107">
<td class="vc_file_line_number">107</td>

<td class="vc_file_line_text">    <span class="pygments-n">w_byte</span><span class="pygments-p">((</span><span class="pygments-kt">char</span><span class="pygments-p">)(</span> <span class="pygments-n">x</span>      <span class="pygments-o">&amp;</span> <span class="pygments-mh">0xff</span><span class="pygments-p">),</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l108">
<td class="vc_file_line_number">108</td>

<td class="vc_file_line_text">    <span class="pygments-n">w_byte</span><span class="pygments-p">((</span><span class="pygments-kt">char</span><span class="pygments-p">)((</span><span class="pygments-n">x</span><span class="pygments-o">&gt;&gt;</span> <span class="pygments-mi">8</span><span class="pygments-p">)</span> <span class="pygments-o">&amp;</span> <span class="pygments-mh">0xff</span><span class="pygments-p">),</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l109">
<td class="vc_file_line_number">109</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l110">
<td class="vc_file_line_number">110</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l111">
<td class="vc_file_line_number">111</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-kt">void</span>
</td>
</tr>




<tr class="vc_row_odd" id="l112">
<td class="vc_file_line_number">112</td>

<td class="vc_file_line_text"><span class="pygments-nf">w_long</span><span class="pygments-p">(</span><span class="pygments-kt">long</span> <span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-n">WFILE</span> <span class="pygments-o">*</span><span class="pygments-n">p</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l113">
<td class="vc_file_line_number">113</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l114">
<td class="vc_file_line_number">114</td>

<td class="vc_file_line_text">    <span class="pygments-n">w_byte</span><span class="pygments-p">((</span><span class="pygments-kt">char</span><span class="pygments-p">)(</span> <span class="pygments-n">x</span>      <span class="pygments-o">&amp;</span> <span class="pygments-mh">0xff</span><span class="pygments-p">),</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l115">
<td class="vc_file_line_number">115</td>

<td class="vc_file_line_text">    <span class="pygments-n">w_byte</span><span class="pygments-p">((</span><span class="pygments-kt">char</span><span class="pygments-p">)((</span><span class="pygments-n">x</span><span class="pygments-o">&gt;&gt;</span> <span class="pygments-mi">8</span><span class="pygments-p">)</span> <span class="pygments-o">&amp;</span> <span class="pygments-mh">0xff</span><span class="pygments-p">),</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l116">
<td class="vc_file_line_number">116</td>

<td class="vc_file_line_text">    <span class="pygments-n">w_byte</span><span class="pygments-p">((</span><span class="pygments-kt">char</span><span class="pygments-p">)((</span><span class="pygments-n">x</span><span class="pygments-o">&gt;&gt;</span><span class="pygments-mi">16</span><span class="pygments-p">)</span> <span class="pygments-o">&amp;</span> <span class="pygments-mh">0xff</span><span class="pygments-p">),</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l117">
<td class="vc_file_line_number">117</td>

<td class="vc_file_line_text">    <span class="pygments-n">w_byte</span><span class="pygments-p">((</span><span class="pygments-kt">char</span><span class="pygments-p">)((</span><span class="pygments-n">x</span><span class="pygments-o">&gt;&gt;</span><span class="pygments-mi">24</span><span class="pygments-p">)</span> <span class="pygments-o">&amp;</span> <span class="pygments-mh">0xff</span><span class="pygments-p">),</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l118">
<td class="vc_file_line_number">118</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l119">
<td class="vc_file_line_number">119</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l120">
<td class="vc_file_line_number">120</td>

<td class="vc_file_line_text"><span class="pygments-cp">#if SIZEOF_LONG &gt; 4</span>
</td>
</tr>




<tr class="vc_row_odd" id="l121">
<td class="vc_file_line_number">121</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-kt">void</span>
</td>
</tr>




<tr class="vc_row_odd" id="l122">
<td class="vc_file_line_number">122</td>

<td class="vc_file_line_text"><span class="pygments-nf">w_long64</span><span class="pygments-p">(</span><span class="pygments-kt">long</span> <span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-n">WFILE</span> <span class="pygments-o">*</span><span class="pygments-n">p</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l123">
<td class="vc_file_line_number">123</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l124">
<td class="vc_file_line_number">124</td>

<td class="vc_file_line_text">    <span class="pygments-n">w_long</span><span class="pygments-p">(</span><span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l125">
<td class="vc_file_line_number">125</td>

<td class="vc_file_line_text">    <span class="pygments-n">w_long</span><span class="pygments-p">(</span><span class="pygments-n">x</span><span class="pygments-o">&gt;&gt;</span><span class="pygments-mi">32</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l126">
<td class="vc_file_line_number">126</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l127">
<td class="vc_file_line_number">127</td>

<td class="vc_file_line_text"><span class="pygments-cp">#endif</span>
</td>
</tr>




<tr class="vc_row_odd" id="l128">
<td class="vc_file_line_number">128</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l129">
<td class="vc_file_line_number">129</td>

<td class="vc_file_line_text"><span class="pygments-cm">/* We assume that Python longs are stored internally in base some power of</span>
</td>
</tr>




<tr class="vc_row_odd" id="l130">
<td class="vc_file_line_number">130</td>

<td class="vc_file_line_text"><span class="pygments-cm">   2**15; for the sake of portability we'll always read and write them in base</span>
</td>
</tr>




<tr class="vc_row_odd" id="l131">
<td class="vc_file_line_number">131</td>

<td class="vc_file_line_text"><span class="pygments-cm">   exactly 2**15. */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l132">
<td class="vc_file_line_number">132</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l133">
<td class="vc_file_line_number">133</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define PyLong_MARSHAL_SHIFT 15</span>
</td>
</tr>




<tr class="vc_row_odd" id="l134">
<td class="vc_file_line_number">134</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define PyLong_MARSHAL_BASE ((short)1 &lt;&lt; PyLong_MARSHAL_SHIFT)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l135">
<td class="vc_file_line_number">135</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define PyLong_MARSHAL_MASK (PyLong_MARSHAL_BASE - 1)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l136">
<td class="vc_file_line_number">136</td>

<td class="vc_file_line_text"><span class="pygments-cp">#if PyLong_SHIFT % PyLong_MARSHAL_SHIFT != 0</span>
</td>
</tr>




<tr class="vc_row_odd" id="l137">
<td class="vc_file_line_number">137</td>

<td class="vc_file_line_text"><span class="pygments-cp">#error "PyLong_SHIFT must be a multiple of PyLong_MARSHAL_SHIFT"</span>
</td>
</tr>




<tr class="vc_row_odd" id="l138">
<td class="vc_file_line_number">138</td>

<td class="vc_file_line_text"><span class="pygments-cp">#endif</span>
</td>
</tr>




<tr class="vc_row_odd" id="l139">
<td class="vc_file_line_number">139</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define PyLong_MARSHAL_RATIO (PyLong_SHIFT / PyLong_MARSHAL_SHIFT)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l140">
<td class="vc_file_line_number">140</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l141">
<td class="vc_file_line_number">141</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-kt">void</span>
</td>
</tr>




<tr class="vc_row_odd" id="l142">
<td class="vc_file_line_number">142</td>

<td class="vc_file_line_text"><span class="pygments-nf">w_PyLong</span><span class="pygments-p">(</span><span class="pygments-k">const</span> <span class="pygments-n">PyLongObject</span> <span class="pygments-o">*</span><span class="pygments-n">ob</span><span class="pygments-p">,</span> <span class="pygments-n">WFILE</span> <span class="pygments-o">*</span><span class="pygments-n">p</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l143">
<td class="vc_file_line_number">143</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l144">
<td class="vc_file_line_number">144</td>

<td class="vc_file_line_text">    <span class="pygments-n">Py_ssize_t</span> <span class="pygments-n">i</span><span class="pygments-p">,</span> <span class="pygments-n">j</span><span class="pygments-p">,</span> <span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">l</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l145">
<td class="vc_file_line_number">145</td>

<td class="vc_file_line_text">    <span class="pygments-n">digit</span> <span class="pygments-n">d</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l146">
<td class="vc_file_line_number">146</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l147">
<td class="vc_file_line_number">147</td>

<td class="vc_file_line_text">    <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_LONG</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l148">
<td class="vc_file_line_number">148</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">Py_SIZE</span><span class="pygments-p">(</span><span class="pygments-n">ob</span><span class="pygments-p">)</span> <span class="pygments-o">==</span> <span class="pygments-mi">0</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l149">
<td class="vc_file_line_number">149</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_long</span><span class="pygments-p">((</span><span class="pygments-kt">long</span><span class="pygments-p">)</span><span class="pygments-mi">0</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l150">
<td class="vc_file_line_number">150</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l151">
<td class="vc_file_line_number">151</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l152">
<td class="vc_file_line_number">152</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l153">
<td class="vc_file_line_number">153</td>

<td class="vc_file_line_text">    <span class="pygments-cm">/* set l to number of base PyLong_MARSHAL_BASE digits */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l154">
<td class="vc_file_line_number">154</td>

<td class="vc_file_line_text">    <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">ABS</span><span class="pygments-p">(</span><span class="pygments-n">Py_SIZE</span><span class="pygments-p">(</span><span class="pygments-n">ob</span><span class="pygments-p">));</span>
</td>
</tr>




<tr class="vc_row_odd" id="l155">
<td class="vc_file_line_number">155</td>

<td class="vc_file_line_text">    <span class="pygments-n">l</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-n">n</span><span class="pygments-o">-</span><span class="pygments-mi">1</span><span class="pygments-p">)</span> <span class="pygments-o">*</span> <span class="pygments-n">PyLong_MARSHAL_RATIO</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l156">
<td class="vc_file_line_number">156</td>

<td class="vc_file_line_text">    <span class="pygments-n">d</span> <span class="pygments-o">=</span> <span class="pygments-n">ob</span><span class="pygments-o">-&gt;</span><span class="pygments-n">ob_digit</span><span class="pygments-p">[</span><span class="pygments-n">n</span><span class="pygments-o">-</span><span class="pygments-mi">1</span><span class="pygments-p">];</span>
</td>
</tr>




<tr class="vc_row_odd" id="l157">
<td class="vc_file_line_number">157</td>

<td class="vc_file_line_text">    <span class="pygments-n">assert</span><span class="pygments-p">(</span><span class="pygments-n">d</span> <span class="pygments-o">!=</span> <span class="pygments-mi">0</span><span class="pygments-p">);</span> <span class="pygments-cm">/* a PyLong is always normalized */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l158">
<td class="vc_file_line_number">158</td>

<td class="vc_file_line_text">    <span class="pygments-k">do</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l159">
<td class="vc_file_line_number">159</td>

<td class="vc_file_line_text">        <span class="pygments-n">d</span> <span class="pygments-o">&gt;&gt;=</span> <span class="pygments-n">PyLong_MARSHAL_SHIFT</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l160">
<td class="vc_file_line_number">160</td>

<td class="vc_file_line_text">        <span class="pygments-n">l</span><span class="pygments-o">++</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l161">
<td class="vc_file_line_number">161</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span> <span class="pygments-k">while</span> <span class="pygments-p">(</span><span class="pygments-n">d</span> <span class="pygments-o">!=</span> <span class="pygments-mi">0</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l162">
<td class="vc_file_line_number">162</td>

<td class="vc_file_line_text">    <span class="pygments-n">w_long</span><span class="pygments-p">((</span><span class="pygments-kt">long</span><span class="pygments-p">)(</span><span class="pygments-n">Py_SIZE</span><span class="pygments-p">(</span><span class="pygments-n">ob</span><span class="pygments-p">)</span> <span class="pygments-o">&gt;</span> <span class="pygments-mi">0</span> <span class="pygments-o">?</span> <span class="pygments-n">l</span> <span class="pygments-o">:</span> <span class="pygments-o">-</span><span class="pygments-n">l</span><span class="pygments-p">),</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l163">
<td class="vc_file_line_number">163</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l164">
<td class="vc_file_line_number">164</td>

<td class="vc_file_line_text">    <span class="pygments-k">for</span> <span class="pygments-p">(</span><span class="pygments-n">i</span><span class="pygments-o">=</span><span class="pygments-mi">0</span><span class="pygments-p">;</span> <span class="pygments-n">i</span> <span class="pygments-o">&lt;</span> <span class="pygments-n">n</span><span class="pygments-o">-</span><span class="pygments-mi">1</span><span class="pygments-p">;</span> <span class="pygments-n">i</span><span class="pygments-o">++</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l165">
<td class="vc_file_line_number">165</td>

<td class="vc_file_line_text">        <span class="pygments-n">d</span> <span class="pygments-o">=</span> <span class="pygments-n">ob</span><span class="pygments-o">-&gt;</span><span class="pygments-n">ob_digit</span><span class="pygments-p">[</span><span class="pygments-n">i</span><span class="pygments-p">];</span>
</td>
</tr>




<tr class="vc_row_odd" id="l166">
<td class="vc_file_line_number">166</td>

<td class="vc_file_line_text">        <span class="pygments-k">for</span> <span class="pygments-p">(</span><span class="pygments-n">j</span><span class="pygments-o">=</span><span class="pygments-mi">0</span><span class="pygments-p">;</span> <span class="pygments-n">j</span> <span class="pygments-o">&lt;</span> <span class="pygments-n">PyLong_MARSHAL_RATIO</span><span class="pygments-p">;</span> <span class="pygments-n">j</span><span class="pygments-o">++</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l167">
<td class="vc_file_line_number">167</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_short</span><span class="pygments-p">(</span><span class="pygments-n">d</span> <span class="pygments-o">&amp;</span> <span class="pygments-n">PyLong_MARSHAL_MASK</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l168">
<td class="vc_file_line_number">168</td>

<td class="vc_file_line_text">            <span class="pygments-n">d</span> <span class="pygments-o">&gt;&gt;=</span> <span class="pygments-n">PyLong_MARSHAL_SHIFT</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l169">
<td class="vc_file_line_number">169</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l170">
<td class="vc_file_line_number">170</td>

<td class="vc_file_line_text">        <span class="pygments-n">assert</span> <span class="pygments-p">(</span><span class="pygments-n">d</span> <span class="pygments-o">==</span> <span class="pygments-mi">0</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l171">
<td class="vc_file_line_number">171</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l172">
<td class="vc_file_line_number">172</td>

<td class="vc_file_line_text">    <span class="pygments-n">d</span> <span class="pygments-o">=</span> <span class="pygments-n">ob</span><span class="pygments-o">-&gt;</span><span class="pygments-n">ob_digit</span><span class="pygments-p">[</span><span class="pygments-n">n</span><span class="pygments-o">-</span><span class="pygments-mi">1</span><span class="pygments-p">];</span>
</td>
</tr>




<tr class="vc_row_odd" id="l173">
<td class="vc_file_line_number">173</td>

<td class="vc_file_line_text">    <span class="pygments-k">do</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l174">
<td class="vc_file_line_number">174</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_short</span><span class="pygments-p">(</span><span class="pygments-n">d</span> <span class="pygments-o">&amp;</span> <span class="pygments-n">PyLong_MARSHAL_MASK</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l175">
<td class="vc_file_line_number">175</td>

<td class="vc_file_line_text">        <span class="pygments-n">d</span> <span class="pygments-o">&gt;&gt;=</span> <span class="pygments-n">PyLong_MARSHAL_SHIFT</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l176">
<td class="vc_file_line_number">176</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span> <span class="pygments-k">while</span> <span class="pygments-p">(</span><span class="pygments-n">d</span> <span class="pygments-o">!=</span> <span class="pygments-mi">0</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l177">
<td class="vc_file_line_number">177</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l178">
<td class="vc_file_line_number">178</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l179">
<td class="vc_file_line_number">179</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-kt">void</span>
</td>
</tr>




<tr class="vc_row_odd" id="l180">
<td class="vc_file_line_number">180</td>

<td class="vc_file_line_text"><span class="pygments-nf">w_object</span><span class="pygments-p">(</span><span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">v</span><span class="pygments-p">,</span> <span class="pygments-n">WFILE</span> <span class="pygments-o">*</span><span class="pygments-n">p</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l181">
<td class="vc_file_line_number">181</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l182">
<td class="vc_file_line_number">182</td>

<td class="vc_file_line_text">    <span class="pygments-n">Py_ssize_t</span> <span class="pygments-n">i</span><span class="pygments-p">,</span> <span class="pygments-n">n</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l183">
<td class="vc_file_line_number">183</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l184">
<td class="vc_file_line_number">184</td>

<td class="vc_file_line_text">    <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">depth</span><span class="pygments-o">++</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l185">
<td class="vc_file_line_number">185</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l186">
<td class="vc_file_line_number">186</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">depth</span> <span class="pygments-o">&gt;</span> <span class="pygments-n">MAX_MARSHAL_STACK_DEPTH</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l187">
<td class="vc_file_line_number">187</td>

<td class="vc_file_line_text">        <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_NESTEDTOODEEP</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l188">
<td class="vc_file_line_number">188</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l189">
<td class="vc_file_line_number">189</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">v</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l190">
<td class="vc_file_line_number">190</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_NULL</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l191">
<td class="vc_file_line_number">191</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l192">
<td class="vc_file_line_number">192</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">v</span> <span class="pygments-o">==</span> <span class="pygments-n">Py_None</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l193">
<td class="vc_file_line_number">193</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_NONE</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l194">
<td class="vc_file_line_number">194</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l195">
<td class="vc_file_line_number">195</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">v</span> <span class="pygments-o">==</span> <span class="pygments-n">PyExc_StopIteration</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l196">
<td class="vc_file_line_number">196</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_STOPITER</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l197">
<td class="vc_file_line_number">197</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l198">
<td class="vc_file_line_number">198</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">v</span> <span class="pygments-o">==</span> <span class="pygments-n">Py_Ellipsis</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l199">
<td class="vc_file_line_number">199</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_ELLIPSIS</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l200">
<td class="vc_file_line_number">200</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l201">
<td class="vc_file_line_number">201</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">v</span> <span class="pygments-o">==</span> <span class="pygments-n">Py_False</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l202">
<td class="vc_file_line_number">202</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_FALSE</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l203">
<td class="vc_file_line_number">203</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l204">
<td class="vc_file_line_number">204</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">v</span> <span class="pygments-o">==</span> <span class="pygments-n">Py_True</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l205">
<td class="vc_file_line_number">205</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_TRUE</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l206">
<td class="vc_file_line_number">206</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l207">
<td class="vc_file_line_number">207</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyInt_CheckExact</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l208">
<td class="vc_file_line_number">208</td>

<td class="vc_file_line_text">        <span class="pygments-kt">long</span> <span class="pygments-n">x</span> <span class="pygments-o">=</span> <span class="pygments-n">PyInt_AS_LONG</span><span class="pygments-p">((</span><span class="pygments-n">PyIntObject</span> <span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l209">
<td class="vc_file_line_number">209</td>

<td class="vc_file_line_text"><span class="pygments-cp">#if SIZEOF_LONG &gt; 4</span>
</td>
</tr>




<tr class="vc_row_odd" id="l210">
<td class="vc_file_line_number">210</td>

<td class="vc_file_line_text">        <span class="pygments-kt">long</span> <span class="pygments-n">y</span> <span class="pygments-o">=</span> <span class="pygments-n">Py_ARITHMETIC_RIGHT_SHIFT</span><span class="pygments-p">(</span><span class="pygments-kt">long</span><span class="pygments-p">,</span> <span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-mi">31</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l211">
<td class="vc_file_line_number">211</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">y</span> <span class="pygments-o">&amp;&amp;</span> <span class="pygments-n">y</span> <span class="pygments-o">!=</span> <span class="pygments-o">-</span><span class="pygments-mi">1</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l212">
<td class="vc_file_line_number">212</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_INT64</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l213">
<td class="vc_file_line_number">213</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_long64</span><span class="pygments-p">(</span><span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l214">
<td class="vc_file_line_number">214</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l215">
<td class="vc_file_line_number">215</td>

<td class="vc_file_line_text">        <span class="pygments-k">else</span>
</td>
</tr>




<tr class="vc_row_odd" id="l216">
<td class="vc_file_line_number">216</td>

<td class="vc_file_line_text"><span class="pygments-cp">#endif</span>
</td>
</tr>




<tr class="vc_row_odd" id="l217">
<td class="vc_file_line_number">217</td>

<td class="vc_file_line_text">            <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l218">
<td class="vc_file_line_number">218</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_INT</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l219">
<td class="vc_file_line_number">219</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_long</span><span class="pygments-p">(</span><span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l220">
<td class="vc_file_line_number">220</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l221">
<td class="vc_file_line_number">221</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l222">
<td class="vc_file_line_number">222</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyLong_CheckExact</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l223">
<td class="vc_file_line_number">223</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyLongObject</span> <span class="pygments-o">*</span><span class="pygments-n">ob</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-n">PyLongObject</span> <span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">v</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l224">
<td class="vc_file_line_number">224</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_PyLong</span><span class="pygments-p">(</span><span class="pygments-n">ob</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l225">
<td class="vc_file_line_number">225</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l226">
<td class="vc_file_line_number">226</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyFloat_CheckExact</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l227">
<td class="vc_file_line_number">227</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">version</span> <span class="pygments-o">&gt;</span> <span class="pygments-mi">1</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l228">
<td class="vc_file_line_number">228</td>

<td class="vc_file_line_text">            <span class="pygments-kt">unsigned</span> <span class="pygments-kt">char</span> <span class="pygments-n">buf</span><span class="pygments-p">[</span><span class="pygments-mi">8</span><span class="pygments-p">];</span>
</td>
</tr>




<tr class="vc_row_odd" id="l229">
<td class="vc_file_line_number">229</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">_PyFloat_Pack8</span><span class="pygments-p">(</span><span class="pygments-n">PyFloat_AsDouble</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">),</span>
</td>
</tr>




<tr class="vc_row_odd" id="l230">
<td class="vc_file_line_number">230</td>

<td class="vc_file_line_text">                               <span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-mi">1</span><span class="pygments-p">)</span> <span class="pygments-o">&lt;</span> <span class="pygments-mi">0</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l231">
<td class="vc_file_line_number">231</td>

<td class="vc_file_line_text">                <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_UNMARSHALLABLE</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l232">
<td class="vc_file_line_number">232</td>

<td class="vc_file_line_text">                <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l233">
<td class="vc_file_line_number">233</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l234">
<td class="vc_file_line_number">234</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_BINARY_FLOAT</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l235">
<td class="vc_file_line_number">235</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_string</span><span class="pygments-p">((</span><span class="pygments-kt">char</span><span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-mi">8</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l236">
<td class="vc_file_line_number">236</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l237">
<td class="vc_file_line_number">237</td>

<td class="vc_file_line_text">        <span class="pygments-k">else</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l238">
<td class="vc_file_line_number">238</td>

<td class="vc_file_line_text">            <span class="pygments-kt">char</span> <span class="pygments-o">*</span><span class="pygments-n">buf</span> <span class="pygments-o">=</span> <span class="pygments-n">PyOS_double_to_string</span><span class="pygments-p">(</span><span class="pygments-n">PyFloat_AS_DOUBLE</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">),</span>
</td>
</tr>




<tr class="vc_row_odd" id="l239">
<td class="vc_file_line_number">239</td>

<td class="vc_file_line_text">                                              <span class="pygments-sc">'g'</span><span class="pygments-p">,</span> <span class="pygments-mi">17</span><span class="pygments-p">,</span> <span class="pygments-mi">0</span><span class="pygments-p">,</span> <span class="pygments-nb">NULL</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l240">
<td class="vc_file_line_number">240</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-o">!</span><span class="pygments-n">buf</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l241">
<td class="vc_file_line_number">241</td>

<td class="vc_file_line_text">                <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_NOMEMORY</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l242">
<td class="vc_file_line_number">242</td>

<td class="vc_file_line_text">                <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l243">
<td class="vc_file_line_number">243</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l244">
<td class="vc_file_line_number">244</td>

<td class="vc_file_line_text">            <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">strlen</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l245">
<td class="vc_file_line_number">245</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_FLOAT</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l246">
<td class="vc_file_line_number">246</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_byte</span><span class="pygments-p">((</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l247">
<td class="vc_file_line_number">247</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_string</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l248">
<td class="vc_file_line_number">248</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyMem_Free</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l249">
<td class="vc_file_line_number">249</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l250">
<td class="vc_file_line_number">250</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l251">
<td class="vc_file_line_number">251</td>

<td class="vc_file_line_text"><span class="pygments-cp">#ifndef WITHOUT_COMPLEX</span>
</td>
</tr>




<tr class="vc_row_odd" id="l252">
<td class="vc_file_line_number">252</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyComplex_CheckExact</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l253">
<td class="vc_file_line_number">253</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">version</span> <span class="pygments-o">&gt;</span> <span class="pygments-mi">1</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l254">
<td class="vc_file_line_number">254</td>

<td class="vc_file_line_text">            <span class="pygments-kt">unsigned</span> <span class="pygments-kt">char</span> <span class="pygments-n">buf</span><span class="pygments-p">[</span><span class="pygments-mi">8</span><span class="pygments-p">];</span>
</td>
</tr>




<tr class="vc_row_odd" id="l255">
<td class="vc_file_line_number">255</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">_PyFloat_Pack8</span><span class="pygments-p">(</span><span class="pygments-n">PyComplex_RealAsDouble</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">),</span>
</td>
</tr>




<tr class="vc_row_odd" id="l256">
<td class="vc_file_line_number">256</td>

<td class="vc_file_line_text">                               <span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-mi">1</span><span class="pygments-p">)</span> <span class="pygments-o">&lt;</span> <span class="pygments-mi">0</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l257">
<td class="vc_file_line_number">257</td>

<td class="vc_file_line_text">                <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_UNMARSHALLABLE</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l258">
<td class="vc_file_line_number">258</td>

<td class="vc_file_line_text">                <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l259">
<td class="vc_file_line_number">259</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l260">
<td class="vc_file_line_number">260</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_BINARY_COMPLEX</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l261">
<td class="vc_file_line_number">261</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_string</span><span class="pygments-p">((</span><span class="pygments-kt">char</span><span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-mi">8</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l262">
<td class="vc_file_line_number">262</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">_PyFloat_Pack8</span><span class="pygments-p">(</span><span class="pygments-n">PyComplex_ImagAsDouble</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">),</span>
</td>
</tr>




<tr class="vc_row_odd" id="l263">
<td class="vc_file_line_number">263</td>

<td class="vc_file_line_text">                               <span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-mi">1</span><span class="pygments-p">)</span> <span class="pygments-o">&lt;</span> <span class="pygments-mi">0</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l264">
<td class="vc_file_line_number">264</td>

<td class="vc_file_line_text">                <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_UNMARSHALLABLE</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l265">
<td class="vc_file_line_number">265</td>

<td class="vc_file_line_text">                <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l266">
<td class="vc_file_line_number">266</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l267">
<td class="vc_file_line_number">267</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_string</span><span class="pygments-p">((</span><span class="pygments-kt">char</span><span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-mi">8</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l268">
<td class="vc_file_line_number">268</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l269">
<td class="vc_file_line_number">269</td>

<td class="vc_file_line_text">        <span class="pygments-k">else</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l270">
<td class="vc_file_line_number">270</td>

<td class="vc_file_line_text">            <span class="pygments-kt">char</span> <span class="pygments-o">*</span><span class="pygments-n">buf</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l271">
<td class="vc_file_line_number">271</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_COMPLEX</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l272">
<td class="vc_file_line_number">272</td>

<td class="vc_file_line_text">            <span class="pygments-n">buf</span> <span class="pygments-o">=</span> <span class="pygments-n">PyOS_double_to_string</span><span class="pygments-p">(</span><span class="pygments-n">PyComplex_RealAsDouble</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">),</span>
</td>
</tr>




<tr class="vc_row_odd" id="l273">
<td class="vc_file_line_number">273</td>

<td class="vc_file_line_text">                                        <span class="pygments-sc">'g'</span><span class="pygments-p">,</span> <span class="pygments-mi">17</span><span class="pygments-p">,</span> <span class="pygments-mi">0</span><span class="pygments-p">,</span> <span class="pygments-nb">NULL</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l274">
<td class="vc_file_line_number">274</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-o">!</span><span class="pygments-n">buf</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l275">
<td class="vc_file_line_number">275</td>

<td class="vc_file_line_text">                <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_NOMEMORY</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l276">
<td class="vc_file_line_number">276</td>

<td class="vc_file_line_text">                <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l277">
<td class="vc_file_line_number">277</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l278">
<td class="vc_file_line_number">278</td>

<td class="vc_file_line_text">            <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">strlen</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l279">
<td class="vc_file_line_number">279</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_byte</span><span class="pygments-p">((</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l280">
<td class="vc_file_line_number">280</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_string</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l281">
<td class="vc_file_line_number">281</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyMem_Free</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l282">
<td class="vc_file_line_number">282</td>

<td class="vc_file_line_text">            <span class="pygments-n">buf</span> <span class="pygments-o">=</span> <span class="pygments-n">PyOS_double_to_string</span><span class="pygments-p">(</span><span class="pygments-n">PyComplex_ImagAsDouble</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">),</span>
</td>
</tr>




<tr class="vc_row_odd" id="l283">
<td class="vc_file_line_number">283</td>

<td class="vc_file_line_text">                                        <span class="pygments-sc">'g'</span><span class="pygments-p">,</span> <span class="pygments-mi">17</span><span class="pygments-p">,</span> <span class="pygments-mi">0</span><span class="pygments-p">,</span> <span class="pygments-nb">NULL</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l284">
<td class="vc_file_line_number">284</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-o">!</span><span class="pygments-n">buf</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l285">
<td class="vc_file_line_number">285</td>

<td class="vc_file_line_text">                <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_NOMEMORY</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l286">
<td class="vc_file_line_number">286</td>

<td class="vc_file_line_text">                <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l287">
<td class="vc_file_line_number">287</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l288">
<td class="vc_file_line_number">288</td>

<td class="vc_file_line_text">            <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">strlen</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l289">
<td class="vc_file_line_number">289</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_byte</span><span class="pygments-p">((</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l290">
<td class="vc_file_line_number">290</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_string</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l291">
<td class="vc_file_line_number">291</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyMem_Free</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l292">
<td class="vc_file_line_number">292</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l293">
<td class="vc_file_line_number">293</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l294">
<td class="vc_file_line_number">294</td>

<td class="vc_file_line_text"><span class="pygments-cp">#endif</span>
</td>
</tr>




<tr class="vc_row_odd" id="l295">
<td class="vc_file_line_number">295</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyString_CheckExact</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l296">
<td class="vc_file_line_number">296</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">strings</span> <span class="pygments-o">&amp;&amp;</span> <span class="pygments-n">PyString_CHECK_INTERNED</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l297">
<td class="vc_file_line_number">297</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">o</span> <span class="pygments-o">=</span> <span class="pygments-n">PyDict_GetItem</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">strings</span><span class="pygments-p">,</span> <span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l298">
<td class="vc_file_line_number">298</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">o</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l299">
<td class="vc_file_line_number">299</td>

<td class="vc_file_line_text">                <span class="pygments-kt">long</span> <span class="pygments-n">w</span> <span class="pygments-o">=</span> <span class="pygments-n">PyInt_AsLong</span><span class="pygments-p">(</span><span class="pygments-n">o</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l300">
<td class="vc_file_line_number">300</td>

<td class="vc_file_line_text">                <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_STRINGREF</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l301">
<td class="vc_file_line_number">301</td>

<td class="vc_file_line_text">                <span class="pygments-n">w_long</span><span class="pygments-p">(</span><span class="pygments-n">w</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l302">
<td class="vc_file_line_number">302</td>

<td class="vc_file_line_text">                <span class="pygments-k">goto</span> <span class="pygments-n">exit</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l303">
<td class="vc_file_line_number">303</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l304">
<td class="vc_file_line_number">304</td>

<td class="vc_file_line_text">            <span class="pygments-k">else</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l305">
<td class="vc_file_line_number">305</td>

<td class="vc_file_line_text">                <span class="pygments-kt">int</span> <span class="pygments-n">ok</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l306">
<td class="vc_file_line_number">306</td>

<td class="vc_file_line_text">                <span class="pygments-n">o</span> <span class="pygments-o">=</span> <span class="pygments-n">PyInt_FromSsize_t</span><span class="pygments-p">(</span><span class="pygments-n">PyDict_Size</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">strings</span><span class="pygments-p">));</span>
</td>
</tr>




<tr class="vc_row_odd" id="l307">
<td class="vc_file_line_number">307</td>

<td class="vc_file_line_text">                <span class="pygments-n">ok</span> <span class="pygments-o">=</span> <span class="pygments-n">o</span> <span class="pygments-o">&amp;&amp;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l308">
<td class="vc_file_line_number">308</td>

<td class="vc_file_line_text">                     <span class="pygments-n">PyDict_SetItem</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">strings</span><span class="pygments-p">,</span> <span class="pygments-n">v</span><span class="pygments-p">,</span> <span class="pygments-n">o</span><span class="pygments-p">)</span> <span class="pygments-o">&gt;=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l309">
<td class="vc_file_line_number">309</td>

<td class="vc_file_line_text">                <span class="pygments-n">Py_XDECREF</span><span class="pygments-p">(</span><span class="pygments-n">o</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l310">
<td class="vc_file_line_number">310</td>

<td class="vc_file_line_text">                <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-o">!</span><span class="pygments-n">ok</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l311">
<td class="vc_file_line_number">311</td>

<td class="vc_file_line_text">                    <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">depth</span><span class="pygments-o">--</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l312">
<td class="vc_file_line_number">312</td>

<td class="vc_file_line_text">                    <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_UNMARSHALLABLE</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l313">
<td class="vc_file_line_number">313</td>

<td class="vc_file_line_text">                    <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l314">
<td class="vc_file_line_number">314</td>

<td class="vc_file_line_text">                <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l315">
<td class="vc_file_line_number">315</td>

<td class="vc_file_line_text">                <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_INTERNED</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l316">
<td class="vc_file_line_number">316</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l317">
<td class="vc_file_line_number">317</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l318">
<td class="vc_file_line_number">318</td>

<td class="vc_file_line_text">        <span class="pygments-k">else</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l319">
<td class="vc_file_line_number">319</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_STRING</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l320">
<td class="vc_file_line_number">320</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l321">
<td class="vc_file_line_number">321</td>

<td class="vc_file_line_text">        <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">PyString_GET_SIZE</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l322">
<td class="vc_file_line_number">322</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">n</span> <span class="pygments-o">&gt;</span> <span class="pygments-n">INT_MAX</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l323">
<td class="vc_file_line_number">323</td>

<td class="vc_file_line_text">            <span class="pygments-cm">/* huge strings are not supported */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l324">
<td class="vc_file_line_number">324</td>

<td class="vc_file_line_text">            <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">depth</span><span class="pygments-o">--</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l325">
<td class="vc_file_line_number">325</td>

<td class="vc_file_line_text">            <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_UNMARSHALLABLE</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l326">
<td class="vc_file_line_number">326</td>

<td class="vc_file_line_text">            <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l327">
<td class="vc_file_line_number">327</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l328">
<td class="vc_file_line_number">328</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_long</span><span class="pygments-p">((</span><span class="pygments-kt">long</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l329">
<td class="vc_file_line_number">329</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_string</span><span class="pygments-p">(</span><span class="pygments-n">PyString_AS_STRING</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">),</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l330">
<td class="vc_file_line_number">330</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l331">
<td class="vc_file_line_number">331</td>

<td class="vc_file_line_text"><span class="pygments-cp">#ifdef Py_USING_UNICODE</span>
</td>
</tr>




<tr class="vc_row_odd" id="l332">
<td class="vc_file_line_number">332</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyUnicode_CheckExact</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l333">
<td class="vc_file_line_number">333</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">utf8</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l334">
<td class="vc_file_line_number">334</td>

<td class="vc_file_line_text">        <span class="pygments-n">utf8</span> <span class="pygments-o">=</span> <span class="pygments-n">PyUnicode_AsUTF8String</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l335">
<td class="vc_file_line_number">335</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">utf8</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l336">
<td class="vc_file_line_number">336</td>

<td class="vc_file_line_text">            <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">depth</span><span class="pygments-o">--</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l337">
<td class="vc_file_line_number">337</td>

<td class="vc_file_line_text">            <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_UNMARSHALLABLE</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l338">
<td class="vc_file_line_number">338</td>

<td class="vc_file_line_text">            <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l339">
<td class="vc_file_line_number">339</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l340">
<td class="vc_file_line_number">340</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_UNICODE</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l341">
<td class="vc_file_line_number">341</td>

<td class="vc_file_line_text">        <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">PyString_GET_SIZE</span><span class="pygments-p">(</span><span class="pygments-n">utf8</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l342">
<td class="vc_file_line_number">342</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">n</span> <span class="pygments-o">&gt;</span> <span class="pygments-n">INT_MAX</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l343">
<td class="vc_file_line_number">343</td>

<td class="vc_file_line_text">            <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">depth</span><span class="pygments-o">--</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l344">
<td class="vc_file_line_number">344</td>

<td class="vc_file_line_text">            <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_UNMARSHALLABLE</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l345">
<td class="vc_file_line_number">345</td>

<td class="vc_file_line_text">            <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l346">
<td class="vc_file_line_number">346</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l347">
<td class="vc_file_line_number">347</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_long</span><span class="pygments-p">((</span><span class="pygments-kt">long</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l348">
<td class="vc_file_line_number">348</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_string</span><span class="pygments-p">(</span><span class="pygments-n">PyString_AS_STRING</span><span class="pygments-p">(</span><span class="pygments-n">utf8</span><span class="pygments-p">),</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l349">
<td class="vc_file_line_number">349</td>

<td class="vc_file_line_text">        <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">utf8</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l350">
<td class="vc_file_line_number">350</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l351">
<td class="vc_file_line_number">351</td>

<td class="vc_file_line_text"><span class="pygments-cp">#endif</span>
</td>
</tr>




<tr class="vc_row_odd" id="l352">
<td class="vc_file_line_number">352</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyTuple_CheckExact</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l353">
<td class="vc_file_line_number">353</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_TUPLE</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l354">
<td class="vc_file_line_number">354</td>

<td class="vc_file_line_text">        <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">PyTuple_Size</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l355">
<td class="vc_file_line_number">355</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_long</span><span class="pygments-p">((</span><span class="pygments-kt">long</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l356">
<td class="vc_file_line_number">356</td>

<td class="vc_file_line_text">        <span class="pygments-k">for</span> <span class="pygments-p">(</span><span class="pygments-n">i</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span> <span class="pygments-n">i</span> <span class="pygments-o">&lt;</span> <span class="pygments-n">n</span><span class="pygments-p">;</span> <span class="pygments-n">i</span><span class="pygments-o">++</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l357">
<td class="vc_file_line_number">357</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">PyTuple_GET_ITEM</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">,</span> <span class="pygments-n">i</span><span class="pygments-p">),</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l358">
<td class="vc_file_line_number">358</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l359">
<td class="vc_file_line_number">359</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l360">
<td class="vc_file_line_number">360</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyList_CheckExact</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l361">
<td class="vc_file_line_number">361</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_LIST</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l362">
<td class="vc_file_line_number">362</td>

<td class="vc_file_line_text">        <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">PyList_GET_SIZE</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l363">
<td class="vc_file_line_number">363</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_long</span><span class="pygments-p">((</span><span class="pygments-kt">long</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l364">
<td class="vc_file_line_number">364</td>

<td class="vc_file_line_text">        <span class="pygments-k">for</span> <span class="pygments-p">(</span><span class="pygments-n">i</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span> <span class="pygments-n">i</span> <span class="pygments-o">&lt;</span> <span class="pygments-n">n</span><span class="pygments-p">;</span> <span class="pygments-n">i</span><span class="pygments-o">++</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l365">
<td class="vc_file_line_number">365</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">PyList_GET_ITEM</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">,</span> <span class="pygments-n">i</span><span class="pygments-p">),</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l366">
<td class="vc_file_line_number">366</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l367">
<td class="vc_file_line_number">367</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l368">
<td class="vc_file_line_number">368</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyDict_CheckExact</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l369">
<td class="vc_file_line_number">369</td>

<td class="vc_file_line_text">        <span class="pygments-n">Py_ssize_t</span> <span class="pygments-n">pos</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l370">
<td class="vc_file_line_number">370</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">key</span><span class="pygments-p">,</span> <span class="pygments-o">*</span><span class="pygments-n">value</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l371">
<td class="vc_file_line_number">371</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_DICT</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l372">
<td class="vc_file_line_number">372</td>

<td class="vc_file_line_text">        <span class="pygments-cm">/* This one is NULL object terminated! */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l373">
<td class="vc_file_line_number">373</td>

<td class="vc_file_line_text">        <span class="pygments-n">pos</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l374">
<td class="vc_file_line_number">374</td>

<td class="vc_file_line_text">        <span class="pygments-k">while</span> <span class="pygments-p">(</span><span class="pygments-n">PyDict_Next</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">pos</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">key</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">value</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l375">
<td class="vc_file_line_number">375</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">key</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l376">
<td class="vc_file_line_number">376</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">value</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l377">
<td class="vc_file_line_number">377</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l378">
<td class="vc_file_line_number">378</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_object</span><span class="pygments-p">((</span><span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-nb">NULL</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l379">
<td class="vc_file_line_number">379</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l380">
<td class="vc_file_line_number">380</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyAnySet_CheckExact</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l381">
<td class="vc_file_line_number">381</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">value</span><span class="pygments-p">,</span> <span class="pygments-o">*</span><span class="pygments-n">it</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l382">
<td class="vc_file_line_number">382</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l383">
<td class="vc_file_line_number">383</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyObject_TypeCheck</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">PySet_Type</span><span class="pygments-p">))</span>
</td>
</tr>




<tr class="vc_row_odd" id="l384">
<td class="vc_file_line_number">384</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_SET</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l385">
<td class="vc_file_line_number">385</td>

<td class="vc_file_line_text">        <span class="pygments-k">else</span>
</td>
</tr>




<tr class="vc_row_odd" id="l386">
<td class="vc_file_line_number">386</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_FROZENSET</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l387">
<td class="vc_file_line_number">387</td>

<td class="vc_file_line_text">        <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">PyObject_Size</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l388">
<td class="vc_file_line_number">388</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">n</span> <span class="pygments-o">==</span> <span class="pygments-o">-</span><span class="pygments-mi">1</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l389">
<td class="vc_file_line_number">389</td>

<td class="vc_file_line_text">            <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">depth</span><span class="pygments-o">--</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l390">
<td class="vc_file_line_number">390</td>

<td class="vc_file_line_text">            <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_UNMARSHALLABLE</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l391">
<td class="vc_file_line_number">391</td>

<td class="vc_file_line_text">            <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l392">
<td class="vc_file_line_number">392</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l393">
<td class="vc_file_line_number">393</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_long</span><span class="pygments-p">((</span><span class="pygments-kt">long</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l394">
<td class="vc_file_line_number">394</td>

<td class="vc_file_line_text">        <span class="pygments-n">it</span> <span class="pygments-o">=</span> <span class="pygments-n">PyObject_GetIter</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l395">
<td class="vc_file_line_number">395</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">it</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l396">
<td class="vc_file_line_number">396</td>

<td class="vc_file_line_text">            <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">depth</span><span class="pygments-o">--</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l397">
<td class="vc_file_line_number">397</td>

<td class="vc_file_line_text">            <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_UNMARSHALLABLE</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l398">
<td class="vc_file_line_number">398</td>

<td class="vc_file_line_text">            <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l399">
<td class="vc_file_line_number">399</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l400">
<td class="vc_file_line_number">400</td>

<td class="vc_file_line_text">        <span class="pygments-k">while</span> <span class="pygments-p">((</span><span class="pygments-n">value</span> <span class="pygments-o">=</span> <span class="pygments-n">PyIter_Next</span><span class="pygments-p">(</span><span class="pygments-n">it</span><span class="pygments-p">))</span> <span class="pygments-o">!=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l401">
<td class="vc_file_line_number">401</td>

<td class="vc_file_line_text">            <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">value</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l402">
<td class="vc_file_line_number">402</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">value</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l403">
<td class="vc_file_line_number">403</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l404">
<td class="vc_file_line_number">404</td>

<td class="vc_file_line_text">        <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">it</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l405">
<td class="vc_file_line_number">405</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyErr_Occurred</span><span class="pygments-p">())</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l406">
<td class="vc_file_line_number">406</td>

<td class="vc_file_line_text">            <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">depth</span><span class="pygments-o">--</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l407">
<td class="vc_file_line_number">407</td>

<td class="vc_file_line_text">            <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_UNMARSHALLABLE</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l408">
<td class="vc_file_line_number">408</td>

<td class="vc_file_line_text">            <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l409">
<td class="vc_file_line_number">409</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l410">
<td class="vc_file_line_number">410</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l411">
<td class="vc_file_line_number">411</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyCode_Check</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l412">
<td class="vc_file_line_number">412</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyCodeObject</span> <span class="pygments-o">*</span><span class="pygments-n">co</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-n">PyCodeObject</span> <span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">v</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l413">
<td class="vc_file_line_number">413</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_CODE</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l414">
<td class="vc_file_line_number">414</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_long</span><span class="pygments-p">(</span><span class="pygments-n">co</span><span class="pygments-o">-&gt;</span><span class="pygments-n">co_argcount</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l415">
<td class="vc_file_line_number">415</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_long</span><span class="pygments-p">(</span><span class="pygments-n">co</span><span class="pygments-o">-&gt;</span><span class="pygments-n">co_nlocals</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l416">
<td class="vc_file_line_number">416</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_long</span><span class="pygments-p">(</span><span class="pygments-n">co</span><span class="pygments-o">-&gt;</span><span class="pygments-n">co_stacksize</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l417">
<td class="vc_file_line_number">417</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_long</span><span class="pygments-p">(</span><span class="pygments-n">co</span><span class="pygments-o">-&gt;</span><span class="pygments-n">co_flags</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l418">
<td class="vc_file_line_number">418</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">co</span><span class="pygments-o">-&gt;</span><span class="pygments-n">co_code</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l419">
<td class="vc_file_line_number">419</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">co</span><span class="pygments-o">-&gt;</span><span class="pygments-n">co_consts</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l420">
<td class="vc_file_line_number">420</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">co</span><span class="pygments-o">-&gt;</span><span class="pygments-n">co_names</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l421">
<td class="vc_file_line_number">421</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">co</span><span class="pygments-o">-&gt;</span><span class="pygments-n">co_varnames</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l422">
<td class="vc_file_line_number">422</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">co</span><span class="pygments-o">-&gt;</span><span class="pygments-n">co_freevars</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l423">
<td class="vc_file_line_number">423</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">co</span><span class="pygments-o">-&gt;</span><span class="pygments-n">co_cellvars</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l424">
<td class="vc_file_line_number">424</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">co</span><span class="pygments-o">-&gt;</span><span class="pygments-n">co_filename</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l425">
<td class="vc_file_line_number">425</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">co</span><span class="pygments-o">-&gt;</span><span class="pygments-n">co_name</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l426">
<td class="vc_file_line_number">426</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_long</span><span class="pygments-p">(</span><span class="pygments-n">co</span><span class="pygments-o">-&gt;</span><span class="pygments-n">co_firstlineno</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l427">
<td class="vc_file_line_number">427</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">co</span><span class="pygments-o">-&gt;</span><span class="pygments-n">co_lnotab</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l428">
<td class="vc_file_line_number">428</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l429">
<td class="vc_file_line_number">429</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyObject_CheckReadBuffer</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l430">
<td class="vc_file_line_number">430</td>

<td class="vc_file_line_text">        <span class="pygments-cm">/* Write unknown buffer-style objects as a string */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l431">
<td class="vc_file_line_number">431</td>

<td class="vc_file_line_text">        <span class="pygments-kt">char</span> <span class="pygments-o">*</span><span class="pygments-n">s</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l432">
<td class="vc_file_line_number">432</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyBufferProcs</span> <span class="pygments-o">*</span><span class="pygments-n">pb</span> <span class="pygments-o">=</span> <span class="pygments-n">v</span><span class="pygments-o">-&gt;</span><span class="pygments-n">ob_type</span><span class="pygments-o">-&gt;</span><span class="pygments-n">tp_as_buffer</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l433">
<td class="vc_file_line_number">433</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_STRING</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l434">
<td class="vc_file_line_number">434</td>

<td class="vc_file_line_text">        <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-o">*</span><span class="pygments-n">pb</span><span class="pygments-o">-&gt;</span><span class="pygments-n">bf_getreadbuffer</span><span class="pygments-p">)(</span><span class="pygments-n">v</span><span class="pygments-p">,</span> <span class="pygments-mi">0</span><span class="pygments-p">,</span> <span class="pygments-p">(</span><span class="pygments-kt">void</span> <span class="pygments-o">**</span><span class="pygments-p">)</span><span class="pygments-o">&amp;</span><span class="pygments-n">s</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l435">
<td class="vc_file_line_number">435</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">n</span> <span class="pygments-o">&gt;</span> <span class="pygments-n">INT_MAX</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l436">
<td class="vc_file_line_number">436</td>

<td class="vc_file_line_text">            <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">depth</span><span class="pygments-o">--</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l437">
<td class="vc_file_line_number">437</td>

<td class="vc_file_line_text">            <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_UNMARSHALLABLE</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l438">
<td class="vc_file_line_number">438</td>

<td class="vc_file_line_text">            <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l439">
<td class="vc_file_line_number">439</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l440">
<td class="vc_file_line_number">440</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_long</span><span class="pygments-p">((</span><span class="pygments-kt">long</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l441">
<td class="vc_file_line_number">441</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_string</span><span class="pygments-p">(</span><span class="pygments-n">s</span><span class="pygments-p">,</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l442">
<td class="vc_file_line_number">442</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l443">
<td class="vc_file_line_number">443</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l444">
<td class="vc_file_line_number">444</td>

<td class="vc_file_line_text">        <span class="pygments-n">w_byte</span><span class="pygments-p">(</span><span class="pygments-n">TYPE_UNKNOWN</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l445">
<td class="vc_file_line_number">445</td>

<td class="vc_file_line_text">        <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_UNMARSHALLABLE</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l446">
<td class="vc_file_line_number">446</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l447">
<td class="vc_file_line_number">447</td>

<td class="vc_file_line_text">   <span class="pygments-nl">exit:</span>
</td>
</tr>




<tr class="vc_row_odd" id="l448">
<td class="vc_file_line_number">448</td>

<td class="vc_file_line_text">    <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">depth</span><span class="pygments-o">--</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l449">
<td class="vc_file_line_number">449</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l450">
<td class="vc_file_line_number">450</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l451">
<td class="vc_file_line_number">451</td>

<td class="vc_file_line_text"><span class="pygments-cm">/* version currently has no effect for writing longs. */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l452">
<td class="vc_file_line_number">452</td>

<td class="vc_file_line_text"><span class="pygments-kt">void</span>
</td>
</tr>




<tr class="vc_row_odd" id="l453">
<td class="vc_file_line_number">453</td>

<td class="vc_file_line_text"><span class="pygments-nf">PyMarshal_WriteLongToFile</span><span class="pygments-p">(</span><span class="pygments-kt">long</span> <span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-kt">FILE</span> <span class="pygments-o">*</span><span class="pygments-n">fp</span><span class="pygments-p">,</span> <span class="pygments-kt">int</span> <span class="pygments-n">version</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l454">
<td class="vc_file_line_number">454</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l455">
<td class="vc_file_line_number">455</td>

<td class="vc_file_line_text">    <span class="pygments-n">WFILE</span> <span class="pygments-n">wf</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l456">
<td class="vc_file_line_number">456</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">fp</span> <span class="pygments-o">=</span> <span class="pygments-n">fp</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l457">
<td class="vc_file_line_number">457</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_OK</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l458">
<td class="vc_file_line_number">458</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">depth</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l459">
<td class="vc_file_line_number">459</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l460">
<td class="vc_file_line_number">460</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">version</span> <span class="pygments-o">=</span> <span class="pygments-n">version</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l461">
<td class="vc_file_line_number">461</td>

<td class="vc_file_line_text">    <span class="pygments-n">w_long</span><span class="pygments-p">(</span><span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">wf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l462">
<td class="vc_file_line_number">462</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l463">
<td class="vc_file_line_number">463</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l464">
<td class="vc_file_line_number">464</td>

<td class="vc_file_line_text"><span class="pygments-kt">void</span>
</td>
</tr>




<tr class="vc_row_odd" id="l465">
<td class="vc_file_line_number">465</td>

<td class="vc_file_line_text"><span class="pygments-nf">PyMarshal_WriteObjectToFile</span><span class="pygments-p">(</span><span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-kt">FILE</span> <span class="pygments-o">*</span><span class="pygments-n">fp</span><span class="pygments-p">,</span> <span class="pygments-kt">int</span> <span class="pygments-n">version</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l466">
<td class="vc_file_line_number">466</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l467">
<td class="vc_file_line_number">467</td>

<td class="vc_file_line_text">    <span class="pygments-n">WFILE</span> <span class="pygments-n">wf</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l468">
<td class="vc_file_line_number">468</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">fp</span> <span class="pygments-o">=</span> <span class="pygments-n">fp</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l469">
<td class="vc_file_line_number">469</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_OK</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l470">
<td class="vc_file_line_number">470</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">depth</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l471">
<td class="vc_file_line_number">471</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-n">version</span> <span class="pygments-o">&gt;</span> <span class="pygments-mi">0</span><span class="pygments-p">)</span> <span class="pygments-o">?</span> <span class="pygments-n">PyDict_New</span><span class="pygments-p">()</span> <span class="pygments-o">:</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l472">
<td class="vc_file_line_number">472</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">version</span> <span class="pygments-o">=</span> <span class="pygments-n">version</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l473">
<td class="vc_file_line_number">473</td>

<td class="vc_file_line_text">    <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">wf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l474">
<td class="vc_file_line_number">474</td>

<td class="vc_file_line_text">    <span class="pygments-n">Py_XDECREF</span><span class="pygments-p">(</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l475">
<td class="vc_file_line_number">475</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l476">
<td class="vc_file_line_number">476</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l477">
<td class="vc_file_line_number">477</td>

<td class="vc_file_line_text"><span class="pygments-k">typedef</span> <span class="pygments-n">WFILE</span> <span class="pygments-n">RFILE</span><span class="pygments-p">;</span> <span class="pygments-cm">/* Same struct with different invariants */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l478">
<td class="vc_file_line_number">478</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l479">
<td class="vc_file_line_number">479</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define rs_byte(p) (((p)-&gt;ptr &lt; (p)-&gt;end) ? (unsigned char)*(p)-&gt;ptr++ : EOF)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l480">
<td class="vc_file_line_number">480</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l481">
<td class="vc_file_line_number">481</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define r_byte(p) ((p)-&gt;fp ? getc((p)-&gt;fp) : rs_byte(p))</span>
</td>
</tr>




<tr class="vc_row_odd" id="l482">
<td class="vc_file_line_number">482</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l483">
<td class="vc_file_line_number">483</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-kt">int</span>
</td>
</tr>




<tr class="vc_row_odd" id="l484">
<td class="vc_file_line_number">484</td>

<td class="vc_file_line_text"><span class="pygments-nf">r_string</span><span class="pygments-p">(</span><span class="pygments-kt">char</span> <span class="pygments-o">*</span><span class="pygments-n">s</span><span class="pygments-p">,</span> <span class="pygments-kt">int</span> <span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">RFILE</span> <span class="pygments-o">*</span><span class="pygments-n">p</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l485">
<td class="vc_file_line_number">485</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l486">
<td class="vc_file_line_number">486</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">fp</span> <span class="pygments-o">!=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l487">
<td class="vc_file_line_number">487</td>

<td class="vc_file_line_text">        <span class="pygments-cm">/* The result fits into int because it must be &lt;=n. */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l488">
<td class="vc_file_line_number">488</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">fread</span><span class="pygments-p">(</span><span class="pygments-n">s</span><span class="pygments-p">,</span> <span class="pygments-mi">1</span><span class="pygments-p">,</span> <span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">fp</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l489">
<td class="vc_file_line_number">489</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">end</span> <span class="pygments-o">-</span> <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">ptr</span> <span class="pygments-o">&lt;</span> <span class="pygments-n">n</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l490">
<td class="vc_file_line_number">490</td>

<td class="vc_file_line_text">        <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">end</span> <span class="pygments-o">-</span> <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">ptr</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l491">
<td class="vc_file_line_number">491</td>

<td class="vc_file_line_text">    <span class="pygments-n">memcpy</span><span class="pygments-p">(</span><span class="pygments-n">s</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">ptr</span><span class="pygments-p">,</span> <span class="pygments-n">n</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l492">
<td class="vc_file_line_number">492</td>

<td class="vc_file_line_text">    <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">ptr</span> <span class="pygments-o">+=</span> <span class="pygments-n">n</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l493">
<td class="vc_file_line_number">493</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">n</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l494">
<td class="vc_file_line_number">494</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l495">
<td class="vc_file_line_number">495</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l496">
<td class="vc_file_line_number">496</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-kt">int</span>
</td>
</tr>




<tr class="vc_row_odd" id="l497">
<td class="vc_file_line_number">497</td>

<td class="vc_file_line_text"><span class="pygments-nf">r_short</span><span class="pygments-p">(</span><span class="pygments-n">RFILE</span> <span class="pygments-o">*</span><span class="pygments-n">p</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l498">
<td class="vc_file_line_number">498</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l499">
<td class="vc_file_line_number">499</td>

<td class="vc_file_line_text">    <span class="pygments-k">register</span> <span class="pygments-kt">short</span> <span class="pygments-n">x</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l500">
<td class="vc_file_line_number">500</td>

<td class="vc_file_line_text">    <span class="pygments-n">x</span> <span class="pygments-o">=</span> <span class="pygments-n">r_byte</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l501">
<td class="vc_file_line_number">501</td>

<td class="vc_file_line_text">    <span class="pygments-n">x</span> <span class="pygments-o">|=</span> <span class="pygments-n">r_byte</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">)</span> <span class="pygments-o">&lt;&lt;</span> <span class="pygments-mi">8</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l502">
<td class="vc_file_line_number">502</td>

<td class="vc_file_line_text">    <span class="pygments-cm">/* Sign-extension, in case short greater than 16 bits */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l503">
<td class="vc_file_line_number">503</td>

<td class="vc_file_line_text">    <span class="pygments-n">x</span> <span class="pygments-o">|=</span> <span class="pygments-o">-</span><span class="pygments-p">(</span><span class="pygments-n">x</span> <span class="pygments-o">&amp;</span> <span class="pygments-mh">0x8000</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l504">
<td class="vc_file_line_number">504</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">x</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l505">
<td class="vc_file_line_number">505</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l506">
<td class="vc_file_line_number">506</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l507">
<td class="vc_file_line_number">507</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-kt">long</span>
</td>
</tr>




<tr class="vc_row_odd" id="l508">
<td class="vc_file_line_number">508</td>

<td class="vc_file_line_text"><span class="pygments-nf">r_long</span><span class="pygments-p">(</span><span class="pygments-n">RFILE</span> <span class="pygments-o">*</span><span class="pygments-n">p</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l509">
<td class="vc_file_line_number">509</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l510">
<td class="vc_file_line_number">510</td>

<td class="vc_file_line_text">    <span class="pygments-k">register</span> <span class="pygments-kt">long</span> <span class="pygments-n">x</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l511">
<td class="vc_file_line_number">511</td>

<td class="vc_file_line_text">    <span class="pygments-k">register</span> <span class="pygments-kt">FILE</span> <span class="pygments-o">*</span><span class="pygments-n">fp</span> <span class="pygments-o">=</span> <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">fp</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l512">
<td class="vc_file_line_number">512</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">fp</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l513">
<td class="vc_file_line_number">513</td>

<td class="vc_file_line_text">        <span class="pygments-n">x</span> <span class="pygments-o">=</span> <span class="pygments-n">getc</span><span class="pygments-p">(</span><span class="pygments-n">fp</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l514">
<td class="vc_file_line_number">514</td>

<td class="vc_file_line_text">        <span class="pygments-n">x</span> <span class="pygments-o">|=</span> <span class="pygments-p">(</span><span class="pygments-kt">long</span><span class="pygments-p">)</span><span class="pygments-n">getc</span><span class="pygments-p">(</span><span class="pygments-n">fp</span><span class="pygments-p">)</span> <span class="pygments-o">&lt;&lt;</span> <span class="pygments-mi">8</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l515">
<td class="vc_file_line_number">515</td>

<td class="vc_file_line_text">        <span class="pygments-n">x</span> <span class="pygments-o">|=</span> <span class="pygments-p">(</span><span class="pygments-kt">long</span><span class="pygments-p">)</span><span class="pygments-n">getc</span><span class="pygments-p">(</span><span class="pygments-n">fp</span><span class="pygments-p">)</span> <span class="pygments-o">&lt;&lt;</span> <span class="pygments-mi">16</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l516">
<td class="vc_file_line_number">516</td>

<td class="vc_file_line_text">        <span class="pygments-n">x</span> <span class="pygments-o">|=</span> <span class="pygments-p">(</span><span class="pygments-kt">long</span><span class="pygments-p">)</span><span class="pygments-n">getc</span><span class="pygments-p">(</span><span class="pygments-n">fp</span><span class="pygments-p">)</span> <span class="pygments-o">&lt;&lt;</span> <span class="pygments-mi">24</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l517">
<td class="vc_file_line_number">517</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l518">
<td class="vc_file_line_number">518</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l519">
<td class="vc_file_line_number">519</td>

<td class="vc_file_line_text">        <span class="pygments-n">x</span> <span class="pygments-o">=</span> <span class="pygments-n">rs_byte</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l520">
<td class="vc_file_line_number">520</td>

<td class="vc_file_line_text">        <span class="pygments-n">x</span> <span class="pygments-o">|=</span> <span class="pygments-p">(</span><span class="pygments-kt">long</span><span class="pygments-p">)</span><span class="pygments-n">rs_byte</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">)</span> <span class="pygments-o">&lt;&lt;</span> <span class="pygments-mi">8</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l521">
<td class="vc_file_line_number">521</td>

<td class="vc_file_line_text">        <span class="pygments-n">x</span> <span class="pygments-o">|=</span> <span class="pygments-p">(</span><span class="pygments-kt">long</span><span class="pygments-p">)</span><span class="pygments-n">rs_byte</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">)</span> <span class="pygments-o">&lt;&lt;</span> <span class="pygments-mi">16</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l522">
<td class="vc_file_line_number">522</td>

<td class="vc_file_line_text">        <span class="pygments-n">x</span> <span class="pygments-o">|=</span> <span class="pygments-p">(</span><span class="pygments-kt">long</span><span class="pygments-p">)</span><span class="pygments-n">rs_byte</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">)</span> <span class="pygments-o">&lt;&lt;</span> <span class="pygments-mi">24</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l523">
<td class="vc_file_line_number">523</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l524">
<td class="vc_file_line_number">524</td>

<td class="vc_file_line_text"><span class="pygments-cp">#if SIZEOF_LONG &gt; 4</span>
</td>
</tr>




<tr class="vc_row_odd" id="l525">
<td class="vc_file_line_number">525</td>

<td class="vc_file_line_text">    <span class="pygments-cm">/* Sign extension for 64-bit machines */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l526">
<td class="vc_file_line_number">526</td>

<td class="vc_file_line_text">    <span class="pygments-n">x</span> <span class="pygments-o">|=</span> <span class="pygments-o">-</span><span class="pygments-p">(</span><span class="pygments-n">x</span> <span class="pygments-o">&amp;</span> <span class="pygments-mh">0x80000000L</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l527">
<td class="vc_file_line_number">527</td>

<td class="vc_file_line_text"><span class="pygments-cp">#endif</span>
</td>
</tr>




<tr class="vc_row_odd" id="l528">
<td class="vc_file_line_number">528</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">x</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l529">
<td class="vc_file_line_number">529</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l530">
<td class="vc_file_line_number">530</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l531">
<td class="vc_file_line_number">531</td>

<td class="vc_file_line_text"><span class="pygments-cm">/* r_long64 deals with the TYPE_INT64 code.  On a machine with</span>
</td>
</tr>




<tr class="vc_row_odd" id="l532">
<td class="vc_file_line_number">532</td>

<td class="vc_file_line_text"><span class="pygments-cm">   sizeof(long) &gt; 4, it returns a Python int object, else a Python long</span>
</td>
</tr>




<tr class="vc_row_odd" id="l533">
<td class="vc_file_line_number">533</td>

<td class="vc_file_line_text"><span class="pygments-cm">   object.  Note that w_long64 writes out TYPE_INT if 32 bits is enough,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l534">
<td class="vc_file_line_number">534</td>

<td class="vc_file_line_text"><span class="pygments-cm">   so there's no inefficiency here in returning a PyLong on 32-bit boxes</span>
</td>
</tr>




<tr class="vc_row_odd" id="l535">
<td class="vc_file_line_number">535</td>

<td class="vc_file_line_text"><span class="pygments-cm">   for everything written via TYPE_INT64 (i.e., if an int is written via</span>
</td>
</tr>




<tr class="vc_row_odd" id="l536">
<td class="vc_file_line_number">536</td>

<td class="vc_file_line_text"><span class="pygments-cm">   TYPE_INT64, it *needs* more than 32 bits).</span>
</td>
</tr>




<tr class="vc_row_odd" id="l537">
<td class="vc_file_line_number">537</td>

<td class="vc_file_line_text"><span class="pygments-cm">*/</span>
</td>
</tr>




<tr class="vc_row_odd" id="l538">
<td class="vc_file_line_number">538</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span>
</td>
</tr>




<tr class="vc_row_odd" id="l539">
<td class="vc_file_line_number">539</td>

<td class="vc_file_line_text"><span class="pygments-nf">r_long64</span><span class="pygments-p">(</span><span class="pygments-n">RFILE</span> <span class="pygments-o">*</span><span class="pygments-n">p</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l540">
<td class="vc_file_line_number">540</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l541">
<td class="vc_file_line_number">541</td>

<td class="vc_file_line_text">    <span class="pygments-kt">long</span> <span class="pygments-n">lo4</span> <span class="pygments-o">=</span> <span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l542">
<td class="vc_file_line_number">542</td>

<td class="vc_file_line_text">    <span class="pygments-kt">long</span> <span class="pygments-n">hi4</span> <span class="pygments-o">=</span> <span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l543">
<td class="vc_file_line_number">543</td>

<td class="vc_file_line_text"><span class="pygments-cp">#if SIZEOF_LONG &gt; 4</span>
</td>
</tr>




<tr class="vc_row_odd" id="l544">
<td class="vc_file_line_number">544</td>

<td class="vc_file_line_text">    <span class="pygments-kt">long</span> <span class="pygments-n">x</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-n">hi4</span> <span class="pygments-o">&lt;&lt;</span> <span class="pygments-mi">32</span><span class="pygments-p">)</span> <span class="pygments-o">|</span> <span class="pygments-p">(</span><span class="pygments-n">lo4</span> <span class="pygments-o">&amp;</span> <span class="pygments-mh">0xFFFFFFFFL</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l545">
<td class="vc_file_line_number">545</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">PyInt_FromLong</span><span class="pygments-p">(</span><span class="pygments-n">x</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l546">
<td class="vc_file_line_number">546</td>

<td class="vc_file_line_text"><span class="pygments-cp">#else</span>
</td>
</tr>




<tr class="vc_row_odd" id="l547">
<td class="vc_file_line_number">547</td>

<td class="vc_file_line_text">    <span class="pygments-kt">unsigned</span> <span class="pygments-kt">char</span> <span class="pygments-n">buf</span><span class="pygments-p">[</span><span class="pygments-mi">8</span><span class="pygments-p">];</span>
</td>
</tr>




<tr class="vc_row_odd" id="l548">
<td class="vc_file_line_number">548</td>

<td class="vc_file_line_text">    <span class="pygments-kt">int</span> <span class="pygments-n">one</span> <span class="pygments-o">=</span> <span class="pygments-mi">1</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l549">
<td class="vc_file_line_number">549</td>

<td class="vc_file_line_text">    <span class="pygments-kt">int</span> <span class="pygments-n">is_little_endian</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-o">*</span><span class="pygments-p">(</span><span class="pygments-kt">char</span><span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-o">&amp;</span><span class="pygments-n">one</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l550">
<td class="vc_file_line_number">550</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">is_little_endian</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l551">
<td class="vc_file_line_number">551</td>

<td class="vc_file_line_text">        <span class="pygments-n">memcpy</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">lo4</span><span class="pygments-p">,</span> <span class="pygments-mi">4</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l552">
<td class="vc_file_line_number">552</td>

<td class="vc_file_line_text">        <span class="pygments-n">memcpy</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-o">+</span><span class="pygments-mi">4</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">hi4</span><span class="pygments-p">,</span> <span class="pygments-mi">4</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l553">
<td class="vc_file_line_number">553</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l554">
<td class="vc_file_line_number">554</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l555">
<td class="vc_file_line_number">555</td>

<td class="vc_file_line_text">        <span class="pygments-n">memcpy</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">hi4</span><span class="pygments-p">,</span> <span class="pygments-mi">4</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l556">
<td class="vc_file_line_number">556</td>

<td class="vc_file_line_text">        <span class="pygments-n">memcpy</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-o">+</span><span class="pygments-mi">4</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">lo4</span><span class="pygments-p">,</span> <span class="pygments-mi">4</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l557">
<td class="vc_file_line_number">557</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l558">
<td class="vc_file_line_number">558</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">_PyLong_FromByteArray</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-mi">8</span><span class="pygments-p">,</span> <span class="pygments-n">is_little_endian</span><span class="pygments-p">,</span> <span class="pygments-mi">1</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l559">
<td class="vc_file_line_number">559</td>

<td class="vc_file_line_text"><span class="pygments-cp">#endif</span>
</td>
</tr>




<tr class="vc_row_odd" id="l560">
<td class="vc_file_line_number">560</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l561">
<td class="vc_file_line_number">561</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l562">
<td class="vc_file_line_number">562</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span>
</td>
</tr>




<tr class="vc_row_odd" id="l563">
<td class="vc_file_line_number">563</td>

<td class="vc_file_line_text"><span class="pygments-nf">r_PyLong</span><span class="pygments-p">(</span><span class="pygments-n">RFILE</span> <span class="pygments-o">*</span><span class="pygments-n">p</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l564">
<td class="vc_file_line_number">564</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l565">
<td class="vc_file_line_number">565</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyLongObject</span> <span class="pygments-o">*</span><span class="pygments-n">ob</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l566">
<td class="vc_file_line_number">566</td>

<td class="vc_file_line_text">    <span class="pygments-kt">int</span> <span class="pygments-n">size</span><span class="pygments-p">,</span> <span class="pygments-n">i</span><span class="pygments-p">,</span> <span class="pygments-n">j</span><span class="pygments-p">,</span> <span class="pygments-n">md</span><span class="pygments-p">,</span> <span class="pygments-n">shorts_in_top_digit</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l567">
<td class="vc_file_line_number">567</td>

<td class="vc_file_line_text">    <span class="pygments-kt">long</span> <span class="pygments-n">n</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l568">
<td class="vc_file_line_number">568</td>

<td class="vc_file_line_text">    <span class="pygments-n">digit</span> <span class="pygments-n">d</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l569">
<td class="vc_file_line_number">569</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l570">
<td class="vc_file_line_number">570</td>

<td class="vc_file_line_text">    <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l571">
<td class="vc_file_line_number">571</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">n</span> <span class="pygments-o">==</span> <span class="pygments-mi">0</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l572">
<td class="vc_file_line_number">572</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-p">(</span><span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">_PyLong_New</span><span class="pygments-p">(</span><span class="pygments-mi">0</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l573">
<td class="vc_file_line_number">573</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">n</span> <span class="pygments-o">&lt;</span> <span class="pygments-o">-</span><span class="pygments-n">INT_MAX</span> <span class="pygments-o">||</span> <span class="pygments-n">n</span> <span class="pygments-o">&gt;</span> <span class="pygments-n">INT_MAX</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l574">
<td class="vc_file_line_number">574</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_ValueError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l575">
<td class="vc_file_line_number">575</td>

<td class="vc_file_line_text">                       <span class="pygments-s">"bad marshal data (long size out of range)"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l576">
<td class="vc_file_line_number">576</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l577">
<td class="vc_file_line_number">577</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l578">
<td class="vc_file_line_number">578</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l579">
<td class="vc_file_line_number">579</td>

<td class="vc_file_line_text">    <span class="pygments-n">size</span> <span class="pygments-o">=</span> <span class="pygments-mi">1</span> <span class="pygments-o">+</span> <span class="pygments-p">(</span><span class="pygments-n">ABS</span><span class="pygments-p">(</span><span class="pygments-n">n</span><span class="pygments-p">)</span> <span class="pygments-o">-</span> <span class="pygments-mi">1</span><span class="pygments-p">)</span> <span class="pygments-o">/</span> <span class="pygments-n">PyLong_MARSHAL_RATIO</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l580">
<td class="vc_file_line_number">580</td>

<td class="vc_file_line_text">    <span class="pygments-n">shorts_in_top_digit</span> <span class="pygments-o">=</span> <span class="pygments-mi">1</span> <span class="pygments-o">+</span> <span class="pygments-p">(</span><span class="pygments-n">ABS</span><span class="pygments-p">(</span><span class="pygments-n">n</span><span class="pygments-p">)</span> <span class="pygments-o">-</span> <span class="pygments-mi">1</span><span class="pygments-p">)</span> <span class="pygments-o">%</span> <span class="pygments-n">PyLong_MARSHAL_RATIO</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l581">
<td class="vc_file_line_number">581</td>

<td class="vc_file_line_text">    <span class="pygments-n">ob</span> <span class="pygments-o">=</span> <span class="pygments-n">_PyLong_New</span><span class="pygments-p">(</span><span class="pygments-n">size</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l582">
<td class="vc_file_line_number">582</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">ob</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l583">
<td class="vc_file_line_number">583</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l584">
<td class="vc_file_line_number">584</td>

<td class="vc_file_line_text">    <span class="pygments-n">Py_SIZE</span><span class="pygments-p">(</span><span class="pygments-n">ob</span><span class="pygments-p">)</span> <span class="pygments-o">=</span> <span class="pygments-n">n</span> <span class="pygments-o">&gt;</span> <span class="pygments-mi">0</span> <span class="pygments-o">?</span> <span class="pygments-n">size</span> <span class="pygments-o">:</span> <span class="pygments-o">-</span><span class="pygments-n">size</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l585">
<td class="vc_file_line_number">585</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l586">
<td class="vc_file_line_number">586</td>

<td class="vc_file_line_text">    <span class="pygments-k">for</span> <span class="pygments-p">(</span><span class="pygments-n">i</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span> <span class="pygments-n">i</span> <span class="pygments-o">&lt;</span> <span class="pygments-n">size</span><span class="pygments-o">-</span><span class="pygments-mi">1</span><span class="pygments-p">;</span> <span class="pygments-n">i</span><span class="pygments-o">++</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l587">
<td class="vc_file_line_number">587</td>

<td class="vc_file_line_text">        <span class="pygments-n">d</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l588">
<td class="vc_file_line_number">588</td>

<td class="vc_file_line_text">        <span class="pygments-k">for</span> <span class="pygments-p">(</span><span class="pygments-n">j</span><span class="pygments-o">=</span><span class="pygments-mi">0</span><span class="pygments-p">;</span> <span class="pygments-n">j</span> <span class="pygments-o">&lt;</span> <span class="pygments-n">PyLong_MARSHAL_RATIO</span><span class="pygments-p">;</span> <span class="pygments-n">j</span><span class="pygments-o">++</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l589">
<td class="vc_file_line_number">589</td>

<td class="vc_file_line_text">            <span class="pygments-n">md</span> <span class="pygments-o">=</span> <span class="pygments-n">r_short</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l590">
<td class="vc_file_line_number">590</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">md</span> <span class="pygments-o">&lt;</span> <span class="pygments-mi">0</span> <span class="pygments-o">||</span> <span class="pygments-n">md</span> <span class="pygments-o">&gt;</span> <span class="pygments-n">PyLong_MARSHAL_BASE</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l591">
<td class="vc_file_line_number">591</td>

<td class="vc_file_line_text">                <span class="pygments-k">goto</span> <span class="pygments-n">bad_digit</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l592">
<td class="vc_file_line_number">592</td>

<td class="vc_file_line_text">            <span class="pygments-n">d</span> <span class="pygments-o">+=</span> <span class="pygments-p">(</span><span class="pygments-n">digit</span><span class="pygments-p">)</span><span class="pygments-n">md</span> <span class="pygments-o">&lt;&lt;</span> <span class="pygments-n">j</span><span class="pygments-o">*</span><span class="pygments-n">PyLong_MARSHAL_SHIFT</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l593">
<td class="vc_file_line_number">593</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l594">
<td class="vc_file_line_number">594</td>

<td class="vc_file_line_text">        <span class="pygments-n">ob</span><span class="pygments-o">-&gt;</span><span class="pygments-n">ob_digit</span><span class="pygments-p">[</span><span class="pygments-n">i</span><span class="pygments-p">]</span> <span class="pygments-o">=</span> <span class="pygments-n">d</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l595">
<td class="vc_file_line_number">595</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l596">
<td class="vc_file_line_number">596</td>

<td class="vc_file_line_text">    <span class="pygments-n">d</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l597">
<td class="vc_file_line_number">597</td>

<td class="vc_file_line_text">    <span class="pygments-k">for</span> <span class="pygments-p">(</span><span class="pygments-n">j</span><span class="pygments-o">=</span><span class="pygments-mi">0</span><span class="pygments-p">;</span> <span class="pygments-n">j</span> <span class="pygments-o">&lt;</span> <span class="pygments-n">shorts_in_top_digit</span><span class="pygments-p">;</span> <span class="pygments-n">j</span><span class="pygments-o">++</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l598">
<td class="vc_file_line_number">598</td>

<td class="vc_file_line_text">        <span class="pygments-n">md</span> <span class="pygments-o">=</span> <span class="pygments-n">r_short</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l599">
<td class="vc_file_line_number">599</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">md</span> <span class="pygments-o">&lt;</span> <span class="pygments-mi">0</span> <span class="pygments-o">||</span> <span class="pygments-n">md</span> <span class="pygments-o">&gt;</span> <span class="pygments-n">PyLong_MARSHAL_BASE</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l600">
<td class="vc_file_line_number">600</td>

<td class="vc_file_line_text">            <span class="pygments-k">goto</span> <span class="pygments-n">bad_digit</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l601">
<td class="vc_file_line_number">601</td>

<td class="vc_file_line_text">        <span class="pygments-cm">/* topmost marshal digit should be nonzero */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l602">
<td class="vc_file_line_number">602</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">md</span> <span class="pygments-o">==</span> <span class="pygments-mi">0</span> <span class="pygments-o">&amp;&amp;</span> <span class="pygments-n">j</span> <span class="pygments-o">==</span> <span class="pygments-n">shorts_in_top_digit</span> <span class="pygments-o">-</span> <span class="pygments-mi">1</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l603">
<td class="vc_file_line_number">603</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">ob</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l604">
<td class="vc_file_line_number">604</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_ValueError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l605">
<td class="vc_file_line_number">605</td>

<td class="vc_file_line_text">                <span class="pygments-s">"bad marshal data (unnormalized long data)"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l606">
<td class="vc_file_line_number">606</td>

<td class="vc_file_line_text">            <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l607">
<td class="vc_file_line_number">607</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l608">
<td class="vc_file_line_number">608</td>

<td class="vc_file_line_text">        <span class="pygments-n">d</span> <span class="pygments-o">+=</span> <span class="pygments-p">(</span><span class="pygments-n">digit</span><span class="pygments-p">)</span><span class="pygments-n">md</span> <span class="pygments-o">&lt;&lt;</span> <span class="pygments-n">j</span><span class="pygments-o">*</span><span class="pygments-n">PyLong_MARSHAL_SHIFT</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l609">
<td class="vc_file_line_number">609</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l610">
<td class="vc_file_line_number">610</td>

<td class="vc_file_line_text">    <span class="pygments-cm">/* top digit should be nonzero, else the resulting PyLong won't be</span>
</td>
</tr>




<tr class="vc_row_odd" id="l611">
<td class="vc_file_line_number">611</td>

<td class="vc_file_line_text"><span class="pygments-cm">       normalized */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l612">
<td class="vc_file_line_number">612</td>

<td class="vc_file_line_text">    <span class="pygments-n">ob</span><span class="pygments-o">-&gt;</span><span class="pygments-n">ob_digit</span><span class="pygments-p">[</span><span class="pygments-n">size</span><span class="pygments-o">-</span><span class="pygments-mi">1</span><span class="pygments-p">]</span> <span class="pygments-o">=</span> <span class="pygments-n">d</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l613">
<td class="vc_file_line_number">613</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-p">(</span><span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">ob</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l614">
<td class="vc_file_line_number">614</td>

<td class="vc_file_line_text">  <span class="pygments-nl">bad_digit:</span>
</td>
</tr>




<tr class="vc_row_odd" id="l615">
<td class="vc_file_line_number">615</td>

<td class="vc_file_line_text">    <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">ob</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l616">
<td class="vc_file_line_number">616</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_ValueError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l617">
<td class="vc_file_line_number">617</td>

<td class="vc_file_line_text">                    <span class="pygments-s">"bad marshal data (digit out of range in long)"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l618">
<td class="vc_file_line_number">618</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l619">
<td class="vc_file_line_number">619</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l620">
<td class="vc_file_line_number">620</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l621">
<td class="vc_file_line_number">621</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l622">
<td class="vc_file_line_number">622</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span>
</td>
</tr>




<tr class="vc_row_odd" id="l623">
<td class="vc_file_line_number">623</td>

<td class="vc_file_line_text"><span class="pygments-nf">r_object</span><span class="pygments-p">(</span><span class="pygments-n">RFILE</span> <span class="pygments-o">*</span><span class="pygments-n">p</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l624">
<td class="vc_file_line_number">624</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l625">
<td class="vc_file_line_number">625</td>

<td class="vc_file_line_text">    <span class="pygments-cm">/* NULL is a valid return value, it does not necessarily means that</span>
</td>
</tr>




<tr class="vc_row_odd" id="l626">
<td class="vc_file_line_number">626</td>

<td class="vc_file_line_text"><span class="pygments-cm">       an exception is set. */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l627">
<td class="vc_file_line_number">627</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">v</span><span class="pygments-p">,</span> <span class="pygments-o">*</span><span class="pygments-n">v2</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l628">
<td class="vc_file_line_number">628</td>

<td class="vc_file_line_text">    <span class="pygments-kt">long</span> <span class="pygments-n">i</span><span class="pygments-p">,</span> <span class="pygments-n">n</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l629">
<td class="vc_file_line_number">629</td>

<td class="vc_file_line_text">    <span class="pygments-kt">int</span> <span class="pygments-n">type</span> <span class="pygments-o">=</span> <span class="pygments-n">r_byte</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l630">
<td class="vc_file_line_number">630</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">retval</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l631">
<td class="vc_file_line_number">631</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l632">
<td class="vc_file_line_number">632</td>

<td class="vc_file_line_text">    <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">depth</span><span class="pygments-o">++</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l633">
<td class="vc_file_line_number">633</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l634">
<td class="vc_file_line_number">634</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">depth</span> <span class="pygments-o">&gt;</span> <span class="pygments-n">MAX_MARSHAL_STACK_DEPTH</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l635">
<td class="vc_file_line_number">635</td>

<td class="vc_file_line_text">        <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">depth</span><span class="pygments-o">--</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l636">
<td class="vc_file_line_number">636</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_ValueError</span><span class="pygments-p">,</span> <span class="pygments-s">"recursion limit exceeded"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l637">
<td class="vc_file_line_number">637</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l638">
<td class="vc_file_line_number">638</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l639">
<td class="vc_file_line_number">639</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l640">
<td class="vc_file_line_number">640</td>

<td class="vc_file_line_text">    <span class="pygments-k">switch</span> <span class="pygments-p">(</span><span class="pygments-n">type</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l641">
<td class="vc_file_line_number">641</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l642">
<td class="vc_file_line_number">642</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">EOF</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l643">
<td class="vc_file_line_number">643</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_EOFError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l644">
<td class="vc_file_line_number">644</td>

<td class="vc_file_line_text">                        <span class="pygments-s">"EOF read where object expected"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l645">
<td class="vc_file_line_number">645</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l646">
<td class="vc_file_line_number">646</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l647">
<td class="vc_file_line_number">647</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l648">
<td class="vc_file_line_number">648</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_NULL</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l649">
<td class="vc_file_line_number">649</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l650">
<td class="vc_file_line_number">650</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l651">
<td class="vc_file_line_number">651</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l652">
<td class="vc_file_line_number">652</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_NONE</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l653">
<td class="vc_file_line_number">653</td>

<td class="vc_file_line_text">        <span class="pygments-n">Py_INCREF</span><span class="pygments-p">(</span><span class="pygments-n">Py_None</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l654">
<td class="vc_file_line_number">654</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">Py_None</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l655">
<td class="vc_file_line_number">655</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l656">
<td class="vc_file_line_number">656</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l657">
<td class="vc_file_line_number">657</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_STOPITER</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l658">
<td class="vc_file_line_number">658</td>

<td class="vc_file_line_text">        <span class="pygments-n">Py_INCREF</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_StopIteration</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l659">
<td class="vc_file_line_number">659</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">PyExc_StopIteration</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l660">
<td class="vc_file_line_number">660</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l661">
<td class="vc_file_line_number">661</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l662">
<td class="vc_file_line_number">662</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_ELLIPSIS</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l663">
<td class="vc_file_line_number">663</td>

<td class="vc_file_line_text">        <span class="pygments-n">Py_INCREF</span><span class="pygments-p">(</span><span class="pygments-n">Py_Ellipsis</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l664">
<td class="vc_file_line_number">664</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">Py_Ellipsis</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l665">
<td class="vc_file_line_number">665</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l666">
<td class="vc_file_line_number">666</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l667">
<td class="vc_file_line_number">667</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_FALSE</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l668">
<td class="vc_file_line_number">668</td>

<td class="vc_file_line_text">        <span class="pygments-n">Py_INCREF</span><span class="pygments-p">(</span><span class="pygments-n">Py_False</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l669">
<td class="vc_file_line_number">669</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">Py_False</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l670">
<td class="vc_file_line_number">670</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l671">
<td class="vc_file_line_number">671</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l672">
<td class="vc_file_line_number">672</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_TRUE</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l673">
<td class="vc_file_line_number">673</td>

<td class="vc_file_line_text">        <span class="pygments-n">Py_INCREF</span><span class="pygments-p">(</span><span class="pygments-n">Py_True</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l674">
<td class="vc_file_line_number">674</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">Py_True</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l675">
<td class="vc_file_line_number">675</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l676">
<td class="vc_file_line_number">676</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l677">
<td class="vc_file_line_number">677</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_INT</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l678">
<td class="vc_file_line_number">678</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">PyInt_FromLong</span><span class="pygments-p">(</span><span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">));</span>
</td>
</tr>




<tr class="vc_row_odd" id="l679">
<td class="vc_file_line_number">679</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l680">
<td class="vc_file_line_number">680</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l681">
<td class="vc_file_line_number">681</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_INT64</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l682">
<td class="vc_file_line_number">682</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">r_long64</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l683">
<td class="vc_file_line_number">683</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l684">
<td class="vc_file_line_number">684</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l685">
<td class="vc_file_line_number">685</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_LONG</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l686">
<td class="vc_file_line_number">686</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">r_PyLong</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l687">
<td class="vc_file_line_number">687</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l688">
<td class="vc_file_line_number">688</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l689">
<td class="vc_file_line_number">689</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_FLOAT</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l690">
<td class="vc_file_line_number">690</td>

<td class="vc_file_line_text">        <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l691">
<td class="vc_file_line_number">691</td>

<td class="vc_file_line_text">            <span class="pygments-kt">char</span> <span class="pygments-n">buf</span><span class="pygments-p">[</span><span class="pygments-mi">256</span><span class="pygments-p">];</span>
</td>
</tr>




<tr class="vc_row_odd" id="l692">
<td class="vc_file_line_number">692</td>

<td class="vc_file_line_text">            <span class="pygments-kt">double</span> <span class="pygments-n">dx</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l693">
<td class="vc_file_line_number">693</td>

<td class="vc_file_line_text">            <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">r_byte</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l694">
<td class="vc_file_line_number">694</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">n</span> <span class="pygments-o">==</span> <span class="pygments-n">EOF</span> <span class="pygments-o">||</span> <span class="pygments-n">r_string</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">)</span> <span class="pygments-o">!=</span> <span class="pygments-n">n</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l695">
<td class="vc_file_line_number">695</td>

<td class="vc_file_line_text">                <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_EOFError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l696">
<td class="vc_file_line_number">696</td>

<td class="vc_file_line_text">                    <span class="pygments-s">"EOF read where object expected"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l697">
<td class="vc_file_line_number">697</td>

<td class="vc_file_line_text">                <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l698">
<td class="vc_file_line_number">698</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l699">
<td class="vc_file_line_number">699</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l700">
<td class="vc_file_line_number">700</td>

<td class="vc_file_line_text">            <span class="pygments-n">buf</span><span class="pygments-p">[</span><span class="pygments-n">n</span><span class="pygments-p">]</span> <span class="pygments-o">=</span> <span class="pygments-sc">'\0'</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l701">
<td class="vc_file_line_number">701</td>

<td class="vc_file_line_text">            <span class="pygments-n">dx</span> <span class="pygments-o">=</span> <span class="pygments-n">PyOS_string_to_double</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-nb">NULL</span><span class="pygments-p">,</span> <span class="pygments-nb">NULL</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l702">
<td class="vc_file_line_number">702</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">dx</span> <span class="pygments-o">==</span> <span class="pygments-o">-</span><span class="pygments-mf">1.0</span> <span class="pygments-o">&amp;&amp;</span> <span class="pygments-n">PyErr_Occurred</span><span class="pygments-p">())</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l703">
<td class="vc_file_line_number">703</td>

<td class="vc_file_line_text">                <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l704">
<td class="vc_file_line_number">704</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l705">
<td class="vc_file_line_number">705</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l706">
<td class="vc_file_line_number">706</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">PyFloat_FromDouble</span><span class="pygments-p">(</span><span class="pygments-n">dx</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l707">
<td class="vc_file_line_number">707</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l708">
<td class="vc_file_line_number">708</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l709">
<td class="vc_file_line_number">709</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l710">
<td class="vc_file_line_number">710</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_BINARY_FLOAT</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l711">
<td class="vc_file_line_number">711</td>

<td class="vc_file_line_text">        <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l712">
<td class="vc_file_line_number">712</td>

<td class="vc_file_line_text">            <span class="pygments-kt">unsigned</span> <span class="pygments-kt">char</span> <span class="pygments-n">buf</span><span class="pygments-p">[</span><span class="pygments-mi">8</span><span class="pygments-p">];</span>
</td>
</tr>




<tr class="vc_row_odd" id="l713">
<td class="vc_file_line_number">713</td>

<td class="vc_file_line_text">            <span class="pygments-kt">double</span> <span class="pygments-n">x</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l714">
<td class="vc_file_line_number">714</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">r_string</span><span class="pygments-p">((</span><span class="pygments-kt">char</span><span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-mi">8</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">)</span> <span class="pygments-o">!=</span> <span class="pygments-mi">8</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l715">
<td class="vc_file_line_number">715</td>

<td class="vc_file_line_text">                <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_EOFError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l716">
<td class="vc_file_line_number">716</td>

<td class="vc_file_line_text">                    <span class="pygments-s">"EOF read where object expected"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l717">
<td class="vc_file_line_number">717</td>

<td class="vc_file_line_text">                <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l718">
<td class="vc_file_line_number">718</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l719">
<td class="vc_file_line_number">719</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l720">
<td class="vc_file_line_number">720</td>

<td class="vc_file_line_text">            <span class="pygments-n">x</span> <span class="pygments-o">=</span> <span class="pygments-n">_PyFloat_Unpack8</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-mi">1</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l721">
<td class="vc_file_line_number">721</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">x</span> <span class="pygments-o">==</span> <span class="pygments-o">-</span><span class="pygments-mf">1.0</span> <span class="pygments-o">&amp;&amp;</span> <span class="pygments-n">PyErr_Occurred</span><span class="pygments-p">())</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l722">
<td class="vc_file_line_number">722</td>

<td class="vc_file_line_text">                <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l723">
<td class="vc_file_line_number">723</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l724">
<td class="vc_file_line_number">724</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l725">
<td class="vc_file_line_number">725</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">PyFloat_FromDouble</span><span class="pygments-p">(</span><span class="pygments-n">x</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l726">
<td class="vc_file_line_number">726</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l727">
<td class="vc_file_line_number">727</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l728">
<td class="vc_file_line_number">728</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l729">
<td class="vc_file_line_number">729</td>

<td class="vc_file_line_text"><span class="pygments-cp">#ifndef WITHOUT_COMPLEX</span>
</td>
</tr>




<tr class="vc_row_odd" id="l730">
<td class="vc_file_line_number">730</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_COMPLEX</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l731">
<td class="vc_file_line_number">731</td>

<td class="vc_file_line_text">        <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l732">
<td class="vc_file_line_number">732</td>

<td class="vc_file_line_text">            <span class="pygments-kt">char</span> <span class="pygments-n">buf</span><span class="pygments-p">[</span><span class="pygments-mi">256</span><span class="pygments-p">];</span>
</td>
</tr>




<tr class="vc_row_odd" id="l733">
<td class="vc_file_line_number">733</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_complex</span> <span class="pygments-n">c</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l734">
<td class="vc_file_line_number">734</td>

<td class="vc_file_line_text">            <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">r_byte</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l735">
<td class="vc_file_line_number">735</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">n</span> <span class="pygments-o">==</span> <span class="pygments-n">EOF</span> <span class="pygments-o">||</span> <span class="pygments-n">r_string</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">)</span> <span class="pygments-o">!=</span> <span class="pygments-n">n</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l736">
<td class="vc_file_line_number">736</td>

<td class="vc_file_line_text">                <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_EOFError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l737">
<td class="vc_file_line_number">737</td>

<td class="vc_file_line_text">                    <span class="pygments-s">"EOF read where object expected"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l738">
<td class="vc_file_line_number">738</td>

<td class="vc_file_line_text">                <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l739">
<td class="vc_file_line_number">739</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l740">
<td class="vc_file_line_number">740</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l741">
<td class="vc_file_line_number">741</td>

<td class="vc_file_line_text">            <span class="pygments-n">buf</span><span class="pygments-p">[</span><span class="pygments-n">n</span><span class="pygments-p">]</span> <span class="pygments-o">=</span> <span class="pygments-sc">'\0'</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l742">
<td class="vc_file_line_number">742</td>

<td class="vc_file_line_text">            <span class="pygments-n">c</span><span class="pygments-p">.</span><span class="pygments-n">real</span> <span class="pygments-o">=</span> <span class="pygments-n">PyOS_string_to_double</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-nb">NULL</span><span class="pygments-p">,</span> <span class="pygments-nb">NULL</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l743">
<td class="vc_file_line_number">743</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">c</span><span class="pygments-p">.</span><span class="pygments-n">real</span> <span class="pygments-o">==</span> <span class="pygments-o">-</span><span class="pygments-mf">1.0</span> <span class="pygments-o">&amp;&amp;</span> <span class="pygments-n">PyErr_Occurred</span><span class="pygments-p">())</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l744">
<td class="vc_file_line_number">744</td>

<td class="vc_file_line_text">                <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l745">
<td class="vc_file_line_number">745</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l746">
<td class="vc_file_line_number">746</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l747">
<td class="vc_file_line_number">747</td>

<td class="vc_file_line_text">            <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">r_byte</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l748">
<td class="vc_file_line_number">748</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">n</span> <span class="pygments-o">==</span> <span class="pygments-n">EOF</span> <span class="pygments-o">||</span> <span class="pygments-n">r_string</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">)</span> <span class="pygments-o">!=</span> <span class="pygments-n">n</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l749">
<td class="vc_file_line_number">749</td>

<td class="vc_file_line_text">                <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_EOFError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l750">
<td class="vc_file_line_number">750</td>

<td class="vc_file_line_text">                    <span class="pygments-s">"EOF read where object expected"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l751">
<td class="vc_file_line_number">751</td>

<td class="vc_file_line_text">                <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l752">
<td class="vc_file_line_number">752</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l753">
<td class="vc_file_line_number">753</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l754">
<td class="vc_file_line_number">754</td>

<td class="vc_file_line_text">            <span class="pygments-n">buf</span><span class="pygments-p">[</span><span class="pygments-n">n</span><span class="pygments-p">]</span> <span class="pygments-o">=</span> <span class="pygments-sc">'\0'</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l755">
<td class="vc_file_line_number">755</td>

<td class="vc_file_line_text">            <span class="pygments-n">c</span><span class="pygments-p">.</span><span class="pygments-n">imag</span> <span class="pygments-o">=</span> <span class="pygments-n">PyOS_string_to_double</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-nb">NULL</span><span class="pygments-p">,</span> <span class="pygments-nb">NULL</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l756">
<td class="vc_file_line_number">756</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">c</span><span class="pygments-p">.</span><span class="pygments-n">imag</span> <span class="pygments-o">==</span> <span class="pygments-o">-</span><span class="pygments-mf">1.0</span> <span class="pygments-o">&amp;&amp;</span> <span class="pygments-n">PyErr_Occurred</span><span class="pygments-p">())</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l757">
<td class="vc_file_line_number">757</td>

<td class="vc_file_line_text">                <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l758">
<td class="vc_file_line_number">758</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l759">
<td class="vc_file_line_number">759</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l760">
<td class="vc_file_line_number">760</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">PyComplex_FromCComplex</span><span class="pygments-p">(</span><span class="pygments-n">c</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l761">
<td class="vc_file_line_number">761</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l762">
<td class="vc_file_line_number">762</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l763">
<td class="vc_file_line_number">763</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l764">
<td class="vc_file_line_number">764</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_BINARY_COMPLEX</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l765">
<td class="vc_file_line_number">765</td>

<td class="vc_file_line_text">        <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l766">
<td class="vc_file_line_number">766</td>

<td class="vc_file_line_text">            <span class="pygments-kt">unsigned</span> <span class="pygments-kt">char</span> <span class="pygments-n">buf</span><span class="pygments-p">[</span><span class="pygments-mi">8</span><span class="pygments-p">];</span>
</td>
</tr>




<tr class="vc_row_odd" id="l767">
<td class="vc_file_line_number">767</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_complex</span> <span class="pygments-n">c</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l768">
<td class="vc_file_line_number">768</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">r_string</span><span class="pygments-p">((</span><span class="pygments-kt">char</span><span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-mi">8</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">)</span> <span class="pygments-o">!=</span> <span class="pygments-mi">8</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l769">
<td class="vc_file_line_number">769</td>

<td class="vc_file_line_text">                <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_EOFError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l770">
<td class="vc_file_line_number">770</td>

<td class="vc_file_line_text">                    <span class="pygments-s">"EOF read where object expected"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l771">
<td class="vc_file_line_number">771</td>

<td class="vc_file_line_text">                <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l772">
<td class="vc_file_line_number">772</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l773">
<td class="vc_file_line_number">773</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l774">
<td class="vc_file_line_number">774</td>

<td class="vc_file_line_text">            <span class="pygments-n">c</span><span class="pygments-p">.</span><span class="pygments-n">real</span> <span class="pygments-o">=</span> <span class="pygments-n">_PyFloat_Unpack8</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-mi">1</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l775">
<td class="vc_file_line_number">775</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">c</span><span class="pygments-p">.</span><span class="pygments-n">real</span> <span class="pygments-o">==</span> <span class="pygments-o">-</span><span class="pygments-mf">1.0</span> <span class="pygments-o">&amp;&amp;</span> <span class="pygments-n">PyErr_Occurred</span><span class="pygments-p">())</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l776">
<td class="vc_file_line_number">776</td>

<td class="vc_file_line_text">                <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l777">
<td class="vc_file_line_number">777</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l778">
<td class="vc_file_line_number">778</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l779">
<td class="vc_file_line_number">779</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">r_string</span><span class="pygments-p">((</span><span class="pygments-kt">char</span><span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-mi">8</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">)</span> <span class="pygments-o">!=</span> <span class="pygments-mi">8</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l780">
<td class="vc_file_line_number">780</td>

<td class="vc_file_line_text">                <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_EOFError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l781">
<td class="vc_file_line_number">781</td>

<td class="vc_file_line_text">                    <span class="pygments-s">"EOF read where object expected"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l782">
<td class="vc_file_line_number">782</td>

<td class="vc_file_line_text">                <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l783">
<td class="vc_file_line_number">783</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l784">
<td class="vc_file_line_number">784</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l785">
<td class="vc_file_line_number">785</td>

<td class="vc_file_line_text">            <span class="pygments-n">c</span><span class="pygments-p">.</span><span class="pygments-n">imag</span> <span class="pygments-o">=</span> <span class="pygments-n">_PyFloat_Unpack8</span><span class="pygments-p">(</span><span class="pygments-n">buf</span><span class="pygments-p">,</span> <span class="pygments-mi">1</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l786">
<td class="vc_file_line_number">786</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">c</span><span class="pygments-p">.</span><span class="pygments-n">imag</span> <span class="pygments-o">==</span> <span class="pygments-o">-</span><span class="pygments-mf">1.0</span> <span class="pygments-o">&amp;&amp;</span> <span class="pygments-n">PyErr_Occurred</span><span class="pygments-p">())</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l787">
<td class="vc_file_line_number">787</td>

<td class="vc_file_line_text">                <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l788">
<td class="vc_file_line_number">788</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l789">
<td class="vc_file_line_number">789</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l790">
<td class="vc_file_line_number">790</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">PyComplex_FromCComplex</span><span class="pygments-p">(</span><span class="pygments-n">c</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l791">
<td class="vc_file_line_number">791</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l792">
<td class="vc_file_line_number">792</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l793">
<td class="vc_file_line_number">793</td>

<td class="vc_file_line_text"><span class="pygments-cp">#endif</span>
</td>
</tr>




<tr class="vc_row_odd" id="l794">
<td class="vc_file_line_number">794</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l795">
<td class="vc_file_line_number">795</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_INTERNED</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l796">
<td class="vc_file_line_number">796</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_STRING</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l797">
<td class="vc_file_line_number">797</td>

<td class="vc_file_line_text">        <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l798">
<td class="vc_file_line_number">798</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">n</span> <span class="pygments-o">&lt;</span> <span class="pygments-mi">0</span> <span class="pygments-o">||</span> <span class="pygments-n">n</span> <span class="pygments-o">&gt;</span> <span class="pygments-n">INT_MAX</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l799">
<td class="vc_file_line_number">799</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_ValueError</span><span class="pygments-p">,</span> <span class="pygments-s">"bad marshal data (string size out of range)"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l800">
<td class="vc_file_line_number">800</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l801">
<td class="vc_file_line_number">801</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l802">
<td class="vc_file_line_number">802</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l803">
<td class="vc_file_line_number">803</td>

<td class="vc_file_line_text">        <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-n">PyString_FromStringAndSize</span><span class="pygments-p">((</span><span class="pygments-kt">char</span> <span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-nb">NULL</span><span class="pygments-p">,</span> <span class="pygments-n">n</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l804">
<td class="vc_file_line_number">804</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">v</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l805">
<td class="vc_file_line_number">805</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l806">
<td class="vc_file_line_number">806</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l807">
<td class="vc_file_line_number">807</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l808">
<td class="vc_file_line_number">808</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">r_string</span><span class="pygments-p">(</span><span class="pygments-n">PyString_AS_STRING</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">),</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">)</span> <span class="pygments-o">!=</span> <span class="pygments-n">n</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l809">
<td class="vc_file_line_number">809</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l810">
<td class="vc_file_line_number">810</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_EOFError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l811">
<td class="vc_file_line_number">811</td>

<td class="vc_file_line_text">                            <span class="pygments-s">"EOF read where object expected"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l812">
<td class="vc_file_line_number">812</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l813">
<td class="vc_file_line_number">813</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l814">
<td class="vc_file_line_number">814</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l815">
<td class="vc_file_line_number">815</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">type</span> <span class="pygments-o">==</span> <span class="pygments-n">TYPE_INTERNED</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l816">
<td class="vc_file_line_number">816</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyString_InternInPlace</span><span class="pygments-p">(</span><span class="pygments-o">&amp;</span><span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l817">
<td class="vc_file_line_number">817</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyList_Append</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">strings</span><span class="pygments-p">,</span> <span class="pygments-n">v</span><span class="pygments-p">)</span> <span class="pygments-o">&lt;</span> <span class="pygments-mi">0</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l818">
<td class="vc_file_line_number">818</td>

<td class="vc_file_line_text">                <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l819">
<td class="vc_file_line_number">819</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l820">
<td class="vc_file_line_number">820</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l821">
<td class="vc_file_line_number">821</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l822">
<td class="vc_file_line_number">822</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">v</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l823">
<td class="vc_file_line_number">823</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l824">
<td class="vc_file_line_number">824</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l825">
<td class="vc_file_line_number">825</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_STRINGREF</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l826">
<td class="vc_file_line_number">826</td>

<td class="vc_file_line_text">        <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l827">
<td class="vc_file_line_number">827</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">n</span> <span class="pygments-o">&lt;</span> <span class="pygments-mi">0</span> <span class="pygments-o">||</span> <span class="pygments-n">n</span> <span class="pygments-o">&gt;=</span> <span class="pygments-n">PyList_GET_SIZE</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">strings</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l828">
<td class="vc_file_line_number">828</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_ValueError</span><span class="pygments-p">,</span> <span class="pygments-s">"bad marshal data (string ref out of range)"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l829">
<td class="vc_file_line_number">829</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l830">
<td class="vc_file_line_number">830</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l831">
<td class="vc_file_line_number">831</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l832">
<td class="vc_file_line_number">832</td>

<td class="vc_file_line_text">        <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-n">PyList_GET_ITEM</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">strings</span><span class="pygments-p">,</span> <span class="pygments-n">n</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l833">
<td class="vc_file_line_number">833</td>

<td class="vc_file_line_text">        <span class="pygments-n">Py_INCREF</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l834">
<td class="vc_file_line_number">834</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">v</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l835">
<td class="vc_file_line_number">835</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l836">
<td class="vc_file_line_number">836</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l837">
<td class="vc_file_line_number">837</td>

<td class="vc_file_line_text"><span class="pygments-cp">#ifdef Py_USING_UNICODE</span>
</td>
</tr>




<tr class="vc_row_odd" id="l838">
<td class="vc_file_line_number">838</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_UNICODE</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l839">
<td class="vc_file_line_number">839</td>

<td class="vc_file_line_text">        <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l840">
<td class="vc_file_line_number">840</td>

<td class="vc_file_line_text">        <span class="pygments-kt">char</span> <span class="pygments-o">*</span><span class="pygments-n">buffer</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l841">
<td class="vc_file_line_number">841</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l842">
<td class="vc_file_line_number">842</td>

<td class="vc_file_line_text">        <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l843">
<td class="vc_file_line_number">843</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">n</span> <span class="pygments-o">&lt;</span> <span class="pygments-mi">0</span> <span class="pygments-o">||</span> <span class="pygments-n">n</span> <span class="pygments-o">&gt;</span> <span class="pygments-n">INT_MAX</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l844">
<td class="vc_file_line_number">844</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_ValueError</span><span class="pygments-p">,</span> <span class="pygments-s">"bad marshal data (unicode size out of range)"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l845">
<td class="vc_file_line_number">845</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l846">
<td class="vc_file_line_number">846</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l847">
<td class="vc_file_line_number">847</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l848">
<td class="vc_file_line_number">848</td>

<td class="vc_file_line_text">        <span class="pygments-n">buffer</span> <span class="pygments-o">=</span> <span class="pygments-n">PyMem_NEW</span><span class="pygments-p">(</span><span class="pygments-kt">char</span><span class="pygments-p">,</span> <span class="pygments-n">n</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l849">
<td class="vc_file_line_number">849</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">buffer</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l850">
<td class="vc_file_line_number">850</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">PyErr_NoMemory</span><span class="pygments-p">();</span>
</td>
</tr>




<tr class="vc_row_odd" id="l851">
<td class="vc_file_line_number">851</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l852">
<td class="vc_file_line_number">852</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l853">
<td class="vc_file_line_number">853</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">r_string</span><span class="pygments-p">(</span><span class="pygments-n">buffer</span><span class="pygments-p">,</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-n">p</span><span class="pygments-p">)</span> <span class="pygments-o">!=</span> <span class="pygments-n">n</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l854">
<td class="vc_file_line_number">854</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyMem_DEL</span><span class="pygments-p">(</span><span class="pygments-n">buffer</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l855">
<td class="vc_file_line_number">855</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_EOFError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l856">
<td class="vc_file_line_number">856</td>

<td class="vc_file_line_text">                <span class="pygments-s">"EOF read where object expected"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l857">
<td class="vc_file_line_number">857</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l858">
<td class="vc_file_line_number">858</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l859">
<td class="vc_file_line_number">859</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l860">
<td class="vc_file_line_number">860</td>

<td class="vc_file_line_text">        <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-n">PyUnicode_DecodeUTF8</span><span class="pygments-p">(</span><span class="pygments-n">buffer</span><span class="pygments-p">,</span> <span class="pygments-n">n</span><span class="pygments-p">,</span> <span class="pygments-nb">NULL</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l861">
<td class="vc_file_line_number">861</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyMem_DEL</span><span class="pygments-p">(</span><span class="pygments-n">buffer</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l862">
<td class="vc_file_line_number">862</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">v</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l863">
<td class="vc_file_line_number">863</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l864">
<td class="vc_file_line_number">864</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l865">
<td class="vc_file_line_number">865</td>

<td class="vc_file_line_text"><span class="pygments-cp">#endif</span>
</td>
</tr>




<tr class="vc_row_odd" id="l866">
<td class="vc_file_line_number">866</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l867">
<td class="vc_file_line_number">867</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_TUPLE</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l868">
<td class="vc_file_line_number">868</td>

<td class="vc_file_line_text">        <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l869">
<td class="vc_file_line_number">869</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">n</span> <span class="pygments-o">&lt;</span> <span class="pygments-mi">0</span> <span class="pygments-o">||</span> <span class="pygments-n">n</span> <span class="pygments-o">&gt;</span> <span class="pygments-n">INT_MAX</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l870">
<td class="vc_file_line_number">870</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_ValueError</span><span class="pygments-p">,</span> <span class="pygments-s">"bad marshal data (tuple size out of range)"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l871">
<td class="vc_file_line_number">871</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l872">
<td class="vc_file_line_number">872</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l873">
<td class="vc_file_line_number">873</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l874">
<td class="vc_file_line_number">874</td>

<td class="vc_file_line_text">        <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-n">PyTuple_New</span><span class="pygments-p">((</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l875">
<td class="vc_file_line_number">875</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">v</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l876">
<td class="vc_file_line_number">876</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l877">
<td class="vc_file_line_number">877</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l878">
<td class="vc_file_line_number">878</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l879">
<td class="vc_file_line_number">879</td>

<td class="vc_file_line_text">        <span class="pygments-k">for</span> <span class="pygments-p">(</span><span class="pygments-n">i</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span> <span class="pygments-n">i</span> <span class="pygments-o">&lt;</span> <span class="pygments-n">n</span><span class="pygments-p">;</span> <span class="pygments-n">i</span><span class="pygments-o">++</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l880">
<td class="vc_file_line_number">880</td>

<td class="vc_file_line_text">            <span class="pygments-n">v2</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l881">
<td class="vc_file_line_number">881</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span> <span class="pygments-n">v2</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span> <span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l882">
<td class="vc_file_line_number">882</td>

<td class="vc_file_line_text">                <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-o">!</span><span class="pygments-n">PyErr_Occurred</span><span class="pygments-p">())</span>
</td>
</tr>




<tr class="vc_row_odd" id="l883">
<td class="vc_file_line_number">883</td>

<td class="vc_file_line_text">                    <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_TypeError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l884">
<td class="vc_file_line_number">884</td>

<td class="vc_file_line_text">                        <span class="pygments-s">"NULL object in marshal data for tuple"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l885">
<td class="vc_file_line_number">885</td>

<td class="vc_file_line_text">                <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l886">
<td class="vc_file_line_number">886</td>

<td class="vc_file_line_text">                <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l887">
<td class="vc_file_line_number">887</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l888">
<td class="vc_file_line_number">888</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l889">
<td class="vc_file_line_number">889</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyTuple_SET_ITEM</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">,</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">i</span><span class="pygments-p">,</span> <span class="pygments-n">v2</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l890">
<td class="vc_file_line_number">890</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l891">
<td class="vc_file_line_number">891</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">v</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l892">
<td class="vc_file_line_number">892</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l893">
<td class="vc_file_line_number">893</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l894">
<td class="vc_file_line_number">894</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_LIST</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l895">
<td class="vc_file_line_number">895</td>

<td class="vc_file_line_text">        <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l896">
<td class="vc_file_line_number">896</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">n</span> <span class="pygments-o">&lt;</span> <span class="pygments-mi">0</span> <span class="pygments-o">||</span> <span class="pygments-n">n</span> <span class="pygments-o">&gt;</span> <span class="pygments-n">INT_MAX</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l897">
<td class="vc_file_line_number">897</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_ValueError</span><span class="pygments-p">,</span> <span class="pygments-s">"bad marshal data (list size out of range)"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l898">
<td class="vc_file_line_number">898</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l899">
<td class="vc_file_line_number">899</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l900">
<td class="vc_file_line_number">900</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l901">
<td class="vc_file_line_number">901</td>

<td class="vc_file_line_text">        <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-n">PyList_New</span><span class="pygments-p">((</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">n</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l902">
<td class="vc_file_line_number">902</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">v</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l903">
<td class="vc_file_line_number">903</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l904">
<td class="vc_file_line_number">904</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l905">
<td class="vc_file_line_number">905</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l906">
<td class="vc_file_line_number">906</td>

<td class="vc_file_line_text">        <span class="pygments-k">for</span> <span class="pygments-p">(</span><span class="pygments-n">i</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span> <span class="pygments-n">i</span> <span class="pygments-o">&lt;</span> <span class="pygments-n">n</span><span class="pygments-p">;</span> <span class="pygments-n">i</span><span class="pygments-o">++</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l907">
<td class="vc_file_line_number">907</td>

<td class="vc_file_line_text">            <span class="pygments-n">v2</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l908">
<td class="vc_file_line_number">908</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span> <span class="pygments-n">v2</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span> <span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l909">
<td class="vc_file_line_number">909</td>

<td class="vc_file_line_text">                <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-o">!</span><span class="pygments-n">PyErr_Occurred</span><span class="pygments-p">())</span>
</td>
</tr>




<tr class="vc_row_odd" id="l910">
<td class="vc_file_line_number">910</td>

<td class="vc_file_line_text">                    <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_TypeError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l911">
<td class="vc_file_line_number">911</td>

<td class="vc_file_line_text">                        <span class="pygments-s">"NULL object in marshal data for list"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l912">
<td class="vc_file_line_number">912</td>

<td class="vc_file_line_text">                <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l913">
<td class="vc_file_line_number">913</td>

<td class="vc_file_line_text">                <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l914">
<td class="vc_file_line_number">914</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l915">
<td class="vc_file_line_number">915</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l916">
<td class="vc_file_line_number">916</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyList_SET_ITEM</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">,</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">i</span><span class="pygments-p">,</span> <span class="pygments-n">v2</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l917">
<td class="vc_file_line_number">917</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l918">
<td class="vc_file_line_number">918</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">v</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l919">
<td class="vc_file_line_number">919</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l920">
<td class="vc_file_line_number">920</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l921">
<td class="vc_file_line_number">921</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_DICT</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l922">
<td class="vc_file_line_number">922</td>

<td class="vc_file_line_text">        <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-n">PyDict_New</span><span class="pygments-p">();</span>
</td>
</tr>




<tr class="vc_row_odd" id="l923">
<td class="vc_file_line_number">923</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">v</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l924">
<td class="vc_file_line_number">924</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l925">
<td class="vc_file_line_number">925</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l926">
<td class="vc_file_line_number">926</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l927">
<td class="vc_file_line_number">927</td>

<td class="vc_file_line_text">        <span class="pygments-k">for</span> <span class="pygments-p">(;;)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l928">
<td class="vc_file_line_number">928</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">key</span><span class="pygments-p">,</span> <span class="pygments-o">*</span><span class="pygments-n">val</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l929">
<td class="vc_file_line_number">929</td>

<td class="vc_file_line_text">            <span class="pygments-n">key</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l930">
<td class="vc_file_line_number">930</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">key</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l931">
<td class="vc_file_line_number">931</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l932">
<td class="vc_file_line_number">932</td>

<td class="vc_file_line_text">            <span class="pygments-n">val</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l933">
<td class="vc_file_line_number">933</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">val</span> <span class="pygments-o">!=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l934">
<td class="vc_file_line_number">934</td>

<td class="vc_file_line_text">                <span class="pygments-n">PyDict_SetItem</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">,</span> <span class="pygments-n">key</span><span class="pygments-p">,</span> <span class="pygments-n">val</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l935">
<td class="vc_file_line_number">935</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">key</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l936">
<td class="vc_file_line_number">936</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_XDECREF</span><span class="pygments-p">(</span><span class="pygments-n">val</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l937">
<td class="vc_file_line_number">937</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l938">
<td class="vc_file_line_number">938</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyErr_Occurred</span><span class="pygments-p">())</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l939">
<td class="vc_file_line_number">939</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l940">
<td class="vc_file_line_number">940</td>

<td class="vc_file_line_text">            <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l941">
<td class="vc_file_line_number">941</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l942">
<td class="vc_file_line_number">942</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">v</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l943">
<td class="vc_file_line_number">943</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l944">
<td class="vc_file_line_number">944</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l945">
<td class="vc_file_line_number">945</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_SET</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l946">
<td class="vc_file_line_number">946</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_FROZENSET</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l947">
<td class="vc_file_line_number">947</td>

<td class="vc_file_line_text">        <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l948">
<td class="vc_file_line_number">948</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">n</span> <span class="pygments-o">&lt;</span> <span class="pygments-mi">0</span> <span class="pygments-o">||</span> <span class="pygments-n">n</span> <span class="pygments-o">&gt;</span> <span class="pygments-n">INT_MAX</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l949">
<td class="vc_file_line_number">949</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_ValueError</span><span class="pygments-p">,</span> <span class="pygments-s">"bad marshal data (set size out of range)"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l950">
<td class="vc_file_line_number">950</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l951">
<td class="vc_file_line_number">951</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l952">
<td class="vc_file_line_number">952</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l953">
<td class="vc_file_line_number">953</td>

<td class="vc_file_line_text">        <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-n">type</span> <span class="pygments-o">==</span> <span class="pygments-n">TYPE_SET</span><span class="pygments-p">)</span> <span class="pygments-o">?</span> <span class="pygments-n">PySet_New</span><span class="pygments-p">(</span><span class="pygments-nb">NULL</span><span class="pygments-p">)</span> <span class="pygments-o">:</span> <span class="pygments-n">PyFrozenSet_New</span><span class="pygments-p">(</span><span class="pygments-nb">NULL</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l954">
<td class="vc_file_line_number">954</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">v</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l955">
<td class="vc_file_line_number">955</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l956">
<td class="vc_file_line_number">956</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l957">
<td class="vc_file_line_number">957</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l958">
<td class="vc_file_line_number">958</td>

<td class="vc_file_line_text">        <span class="pygments-k">for</span> <span class="pygments-p">(</span><span class="pygments-n">i</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span> <span class="pygments-n">i</span> <span class="pygments-o">&lt;</span> <span class="pygments-n">n</span><span class="pygments-p">;</span> <span class="pygments-n">i</span><span class="pygments-o">++</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l959">
<td class="vc_file_line_number">959</td>

<td class="vc_file_line_text">            <span class="pygments-n">v2</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l960">
<td class="vc_file_line_number">960</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span> <span class="pygments-n">v2</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span> <span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l961">
<td class="vc_file_line_number">961</td>

<td class="vc_file_line_text">                <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-o">!</span><span class="pygments-n">PyErr_Occurred</span><span class="pygments-p">())</span>
</td>
</tr>




<tr class="vc_row_odd" id="l962">
<td class="vc_file_line_number">962</td>

<td class="vc_file_line_text">                    <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_TypeError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l963">
<td class="vc_file_line_number">963</td>

<td class="vc_file_line_text">                        <span class="pygments-s">"NULL object in marshal data for set"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l964">
<td class="vc_file_line_number">964</td>

<td class="vc_file_line_text">                <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l965">
<td class="vc_file_line_number">965</td>

<td class="vc_file_line_text">                <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l966">
<td class="vc_file_line_number">966</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l967">
<td class="vc_file_line_number">967</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l968">
<td class="vc_file_line_number">968</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PySet_Add</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">,</span> <span class="pygments-n">v2</span><span class="pygments-p">)</span> <span class="pygments-o">==</span> <span class="pygments-o">-</span><span class="pygments-mi">1</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l969">
<td class="vc_file_line_number">969</td>

<td class="vc_file_line_text">                <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">v</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l970">
<td class="vc_file_line_number">970</td>

<td class="vc_file_line_text">                <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">v2</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l971">
<td class="vc_file_line_number">971</td>

<td class="vc_file_line_text">                <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l972">
<td class="vc_file_line_number">972</td>

<td class="vc_file_line_text">                <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l973">
<td class="vc_file_line_number">973</td>

<td class="vc_file_line_text">            <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l974">
<td class="vc_file_line_number">974</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">v2</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l975">
<td class="vc_file_line_number">975</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l976">
<td class="vc_file_line_number">976</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">v</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l977">
<td class="vc_file_line_number">977</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l978">
<td class="vc_file_line_number">978</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l979">
<td class="vc_file_line_number">979</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">TYPE_CODE</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l980">
<td class="vc_file_line_number">980</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyEval_GetRestricted</span><span class="pygments-p">())</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l981">
<td class="vc_file_line_number">981</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_RuntimeError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l982">
<td class="vc_file_line_number">982</td>

<td class="vc_file_line_text">                <span class="pygments-s">"cannot unmarshal code objects in "</span>
</td>
</tr>




<tr class="vc_row_odd" id="l983">
<td class="vc_file_line_number">983</td>

<td class="vc_file_line_text">                <span class="pygments-s">"restricted execution mode"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l984">
<td class="vc_file_line_number">984</td>

<td class="vc_file_line_text">            <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l985">
<td class="vc_file_line_number">985</td>

<td class="vc_file_line_text">            <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l986">
<td class="vc_file_line_number">986</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l987">
<td class="vc_file_line_number">987</td>

<td class="vc_file_line_text">        <span class="pygments-k">else</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l988">
<td class="vc_file_line_number">988</td>

<td class="vc_file_line_text">            <span class="pygments-kt">int</span> <span class="pygments-n">argcount</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l989">
<td class="vc_file_line_number">989</td>

<td class="vc_file_line_text">            <span class="pygments-kt">int</span> <span class="pygments-n">nlocals</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l990">
<td class="vc_file_line_number">990</td>

<td class="vc_file_line_text">            <span class="pygments-kt">int</span> <span class="pygments-n">stacksize</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l991">
<td class="vc_file_line_number">991</td>

<td class="vc_file_line_text">            <span class="pygments-kt">int</span> <span class="pygments-n">flags</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l992">
<td class="vc_file_line_number">992</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">code</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l993">
<td class="vc_file_line_number">993</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">consts</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l994">
<td class="vc_file_line_number">994</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">names</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l995">
<td class="vc_file_line_number">995</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">varnames</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l996">
<td class="vc_file_line_number">996</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">freevars</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l997">
<td class="vc_file_line_number">997</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">cellvars</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l998">
<td class="vc_file_line_number">998</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">filename</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l999">
<td class="vc_file_line_number">999</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">name</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1000">
<td class="vc_file_line_number">1000</td>

<td class="vc_file_line_text">            <span class="pygments-kt">int</span> <span class="pygments-n">firstlineno</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1001">
<td class="vc_file_line_number">1001</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">lnotab</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1002">
<td class="vc_file_line_number">1002</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1003">
<td class="vc_file_line_number">1003</td>

<td class="vc_file_line_text">            <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1004">
<td class="vc_file_line_number">1004</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1005">
<td class="vc_file_line_number">1005</td>

<td class="vc_file_line_text">            <span class="pygments-cm">/* XXX ignore long-&gt;int overflows for now */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1006">
<td class="vc_file_line_number">1006</td>

<td class="vc_file_line_text">            <span class="pygments-n">argcount</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1007">
<td class="vc_file_line_number">1007</td>

<td class="vc_file_line_text">            <span class="pygments-n">nlocals</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1008">
<td class="vc_file_line_number">1008</td>

<td class="vc_file_line_text">            <span class="pygments-n">stacksize</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1009">
<td class="vc_file_line_number">1009</td>

<td class="vc_file_line_text">            <span class="pygments-n">flags</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1010">
<td class="vc_file_line_number">1010</td>

<td class="vc_file_line_text">            <span class="pygments-n">code</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1011">
<td class="vc_file_line_number">1011</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">code</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1012">
<td class="vc_file_line_number">1012</td>

<td class="vc_file_line_text">                <span class="pygments-k">goto</span> <span class="pygments-n">code_error</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1013">
<td class="vc_file_line_number">1013</td>

<td class="vc_file_line_text">            <span class="pygments-n">consts</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1014">
<td class="vc_file_line_number">1014</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">consts</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1015">
<td class="vc_file_line_number">1015</td>

<td class="vc_file_line_text">                <span class="pygments-k">goto</span> <span class="pygments-n">code_error</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1016">
<td class="vc_file_line_number">1016</td>

<td class="vc_file_line_text">            <span class="pygments-n">names</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1017">
<td class="vc_file_line_number">1017</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">names</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1018">
<td class="vc_file_line_number">1018</td>

<td class="vc_file_line_text">                <span class="pygments-k">goto</span> <span class="pygments-n">code_error</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1019">
<td class="vc_file_line_number">1019</td>

<td class="vc_file_line_text">            <span class="pygments-n">varnames</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1020">
<td class="vc_file_line_number">1020</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">varnames</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1021">
<td class="vc_file_line_number">1021</td>

<td class="vc_file_line_text">                <span class="pygments-k">goto</span> <span class="pygments-n">code_error</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1022">
<td class="vc_file_line_number">1022</td>

<td class="vc_file_line_text">            <span class="pygments-n">freevars</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1023">
<td class="vc_file_line_number">1023</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">freevars</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1024">
<td class="vc_file_line_number">1024</td>

<td class="vc_file_line_text">                <span class="pygments-k">goto</span> <span class="pygments-n">code_error</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1025">
<td class="vc_file_line_number">1025</td>

<td class="vc_file_line_text">            <span class="pygments-n">cellvars</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1026">
<td class="vc_file_line_number">1026</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">cellvars</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1027">
<td class="vc_file_line_number">1027</td>

<td class="vc_file_line_text">                <span class="pygments-k">goto</span> <span class="pygments-n">code_error</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1028">
<td class="vc_file_line_number">1028</td>

<td class="vc_file_line_text">            <span class="pygments-n">filename</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1029">
<td class="vc_file_line_number">1029</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">filename</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1030">
<td class="vc_file_line_number">1030</td>

<td class="vc_file_line_text">                <span class="pygments-k">goto</span> <span class="pygments-n">code_error</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1031">
<td class="vc_file_line_number">1031</td>

<td class="vc_file_line_text">            <span class="pygments-n">name</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1032">
<td class="vc_file_line_number">1032</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">name</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1033">
<td class="vc_file_line_number">1033</td>

<td class="vc_file_line_text">                <span class="pygments-k">goto</span> <span class="pygments-n">code_error</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1034">
<td class="vc_file_line_number">1034</td>

<td class="vc_file_line_text">            <span class="pygments-n">firstlineno</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1035">
<td class="vc_file_line_number">1035</td>

<td class="vc_file_line_text">            <span class="pygments-n">lnotab</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1036">
<td class="vc_file_line_number">1036</td>

<td class="vc_file_line_text">            <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">lnotab</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1037">
<td class="vc_file_line_number">1037</td>

<td class="vc_file_line_text">                <span class="pygments-k">goto</span> <span class="pygments-n">code_error</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1038">
<td class="vc_file_line_number">1038</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1039">
<td class="vc_file_line_number">1039</td>

<td class="vc_file_line_text">            <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-p">)</span> <span class="pygments-n">PyCode_New</span><span class="pygments-p">(</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1040">
<td class="vc_file_line_number">1040</td>

<td class="vc_file_line_text">                            <span class="pygments-n">argcount</span><span class="pygments-p">,</span> <span class="pygments-n">nlocals</span><span class="pygments-p">,</span> <span class="pygments-n">stacksize</span><span class="pygments-p">,</span> <span class="pygments-n">flags</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1041">
<td class="vc_file_line_number">1041</td>

<td class="vc_file_line_text">                            <span class="pygments-n">code</span><span class="pygments-p">,</span> <span class="pygments-n">consts</span><span class="pygments-p">,</span> <span class="pygments-n">names</span><span class="pygments-p">,</span> <span class="pygments-n">varnames</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1042">
<td class="vc_file_line_number">1042</td>

<td class="vc_file_line_text">                            <span class="pygments-n">freevars</span><span class="pygments-p">,</span> <span class="pygments-n">cellvars</span><span class="pygments-p">,</span> <span class="pygments-n">filename</span><span class="pygments-p">,</span> <span class="pygments-n">name</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1043">
<td class="vc_file_line_number">1043</td>

<td class="vc_file_line_text">                            <span class="pygments-n">firstlineno</span><span class="pygments-p">,</span> <span class="pygments-n">lnotab</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1044">
<td class="vc_file_line_number">1044</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1045">
<td class="vc_file_line_number">1045</td>

<td class="vc_file_line_text">          <span class="pygments-nl">code_error:</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1046">
<td class="vc_file_line_number">1046</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_XDECREF</span><span class="pygments-p">(</span><span class="pygments-n">code</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1047">
<td class="vc_file_line_number">1047</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_XDECREF</span><span class="pygments-p">(</span><span class="pygments-n">consts</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1048">
<td class="vc_file_line_number">1048</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_XDECREF</span><span class="pygments-p">(</span><span class="pygments-n">names</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1049">
<td class="vc_file_line_number">1049</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_XDECREF</span><span class="pygments-p">(</span><span class="pygments-n">varnames</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1050">
<td class="vc_file_line_number">1050</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_XDECREF</span><span class="pygments-p">(</span><span class="pygments-n">freevars</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1051">
<td class="vc_file_line_number">1051</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_XDECREF</span><span class="pygments-p">(</span><span class="pygments-n">cellvars</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1052">
<td class="vc_file_line_number">1052</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_XDECREF</span><span class="pygments-p">(</span><span class="pygments-n">filename</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1053">
<td class="vc_file_line_number">1053</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_XDECREF</span><span class="pygments-p">(</span><span class="pygments-n">name</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1054">
<td class="vc_file_line_number">1054</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_XDECREF</span><span class="pygments-p">(</span><span class="pygments-n">lnotab</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1055">
<td class="vc_file_line_number">1055</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1056">
<td class="vc_file_line_number">1056</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1057">
<td class="vc_file_line_number">1057</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-n">v</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1058">
<td class="vc_file_line_number">1058</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1059">
<td class="vc_file_line_number">1059</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1060">
<td class="vc_file_line_number">1060</td>

<td class="vc_file_line_text">    <span class="pygments-nl">default:</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1061">
<td class="vc_file_line_number">1061</td>

<td class="vc_file_line_text">        <span class="pygments-cm">/* Bogus data got written, which isn't ideal.</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1062">
<td class="vc_file_line_number">1062</td>

<td class="vc_file_line_text"><span class="pygments-cm">           This will let you keep working and recover. */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1063">
<td class="vc_file_line_number">1063</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_ValueError</span><span class="pygments-p">,</span> <span class="pygments-s">"bad marshal data (unknown type code)"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1064">
<td class="vc_file_line_number">1064</td>

<td class="vc_file_line_text">        <span class="pygments-n">retval</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1065">
<td class="vc_file_line_number">1065</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1066">
<td class="vc_file_line_number">1066</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1067">
<td class="vc_file_line_number">1067</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1068">
<td class="vc_file_line_number">1068</td>

<td class="vc_file_line_text">    <span class="pygments-n">p</span><span class="pygments-o">-&gt;</span><span class="pygments-n">depth</span><span class="pygments-o">--</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1069">
<td class="vc_file_line_number">1069</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">retval</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1070">
<td class="vc_file_line_number">1070</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1071">
<td class="vc_file_line_number">1071</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1072">
<td class="vc_file_line_number">1072</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1073">
<td class="vc_file_line_number">1073</td>

<td class="vc_file_line_text"><span class="pygments-nf">read_object</span><span class="pygments-p">(</span><span class="pygments-n">RFILE</span> <span class="pygments-o">*</span><span class="pygments-n">p</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1074">
<td class="vc_file_line_number">1074</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1075">
<td class="vc_file_line_number">1075</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">v</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1076">
<td class="vc_file_line_number">1076</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">PyErr_Occurred</span><span class="pygments-p">())</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1077">
<td class="vc_file_line_number">1077</td>

<td class="vc_file_line_text">        <span class="pygments-n">fprintf</span><span class="pygments-p">(</span><span class="pygments-n">stderr</span><span class="pygments-p">,</span> <span class="pygments-s">"XXX readobject called with exception set</span><span class="pygments-se">\n</span><span class="pygments-s">"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1078">
<td class="vc_file_line_number">1078</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1079">
<td class="vc_file_line_number">1079</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1080">
<td class="vc_file_line_number">1080</td>

<td class="vc_file_line_text">    <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-n">p</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1081">
<td class="vc_file_line_number">1081</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">v</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span> <span class="pygments-o">&amp;&amp;</span> <span class="pygments-o">!</span><span class="pygments-n">PyErr_Occurred</span><span class="pygments-p">())</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1082">
<td class="vc_file_line_number">1082</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_TypeError</span><span class="pygments-p">,</span> <span class="pygments-s">"NULL object in marshal data for object"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1083">
<td class="vc_file_line_number">1083</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">v</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1084">
<td class="vc_file_line_number">1084</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1085">
<td class="vc_file_line_number">1085</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1086">
<td class="vc_file_line_number">1086</td>

<td class="vc_file_line_text"><span class="pygments-kt">int</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1087">
<td class="vc_file_line_number">1087</td>

<td class="vc_file_line_text"><span class="pygments-nf">PyMarshal_ReadShortFromFile</span><span class="pygments-p">(</span><span class="pygments-kt">FILE</span> <span class="pygments-o">*</span><span class="pygments-n">fp</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1088">
<td class="vc_file_line_number">1088</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1089">
<td class="vc_file_line_number">1089</td>

<td class="vc_file_line_text">    <span class="pygments-n">RFILE</span> <span class="pygments-n">rf</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1090">
<td class="vc_file_line_number">1090</td>

<td class="vc_file_line_text">    <span class="pygments-n">assert</span><span class="pygments-p">(</span><span class="pygments-n">fp</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1091">
<td class="vc_file_line_number">1091</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">fp</span> <span class="pygments-o">=</span> <span class="pygments-n">fp</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1092">
<td class="vc_file_line_number">1092</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1093">
<td class="vc_file_line_number">1093</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">end</span> <span class="pygments-o">=</span> <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">ptr</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1094">
<td class="vc_file_line_number">1094</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">r_short</span><span class="pygments-p">(</span><span class="pygments-o">&amp;</span><span class="pygments-n">rf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1095">
<td class="vc_file_line_number">1095</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1096">
<td class="vc_file_line_number">1096</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1097">
<td class="vc_file_line_number">1097</td>

<td class="vc_file_line_text"><span class="pygments-kt">long</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1098">
<td class="vc_file_line_number">1098</td>

<td class="vc_file_line_text"><span class="pygments-nf">PyMarshal_ReadLongFromFile</span><span class="pygments-p">(</span><span class="pygments-kt">FILE</span> <span class="pygments-o">*</span><span class="pygments-n">fp</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1099">
<td class="vc_file_line_number">1099</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1100">
<td class="vc_file_line_number">1100</td>

<td class="vc_file_line_text">    <span class="pygments-n">RFILE</span> <span class="pygments-n">rf</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1101">
<td class="vc_file_line_number">1101</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">fp</span> <span class="pygments-o">=</span> <span class="pygments-n">fp</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1102">
<td class="vc_file_line_number">1102</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1103">
<td class="vc_file_line_number">1103</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">ptr</span> <span class="pygments-o">=</span> <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">end</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1104">
<td class="vc_file_line_number">1104</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">r_long</span><span class="pygments-p">(</span><span class="pygments-o">&amp;</span><span class="pygments-n">rf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1105">
<td class="vc_file_line_number">1105</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1106">
<td class="vc_file_line_number">1106</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1107">
<td class="vc_file_line_number">1107</td>

<td class="vc_file_line_text"><span class="pygments-cp">#ifdef HAVE_FSTAT</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1108">
<td class="vc_file_line_number">1108</td>

<td class="vc_file_line_text"><span class="pygments-cm">/* Return size of file in bytes; &lt; 0 if unknown. */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1109">
<td class="vc_file_line_number">1109</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-kt">off_t</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1110">
<td class="vc_file_line_number">1110</td>

<td class="vc_file_line_text"><span class="pygments-nf">getfilesize</span><span class="pygments-p">(</span><span class="pygments-kt">FILE</span> <span class="pygments-o">*</span><span class="pygments-n">fp</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1111">
<td class="vc_file_line_number">1111</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1112">
<td class="vc_file_line_number">1112</td>

<td class="vc_file_line_text">    <span class="pygments-k">struct</span> <span class="pygments-n">stat</span> <span class="pygments-n">st</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1113">
<td class="vc_file_line_number">1113</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">fstat</span><span class="pygments-p">(</span><span class="pygments-n">fileno</span><span class="pygments-p">(</span><span class="pygments-n">fp</span><span class="pygments-p">),</span> <span class="pygments-o">&amp;</span><span class="pygments-n">st</span><span class="pygments-p">)</span> <span class="pygments-o">!=</span> <span class="pygments-mi">0</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1114">
<td class="vc_file_line_number">1114</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-o">-</span><span class="pygments-mi">1</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1115">
<td class="vc_file_line_number">1115</td>

<td class="vc_file_line_text">    <span class="pygments-k">else</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1116">
<td class="vc_file_line_number">1116</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-n">st</span><span class="pygments-p">.</span><span class="pygments-n">st_size</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1117">
<td class="vc_file_line_number">1117</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1118">
<td class="vc_file_line_number">1118</td>

<td class="vc_file_line_text"><span class="pygments-cp">#endif</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1119">
<td class="vc_file_line_number">1119</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1120">
<td class="vc_file_line_number">1120</td>

<td class="vc_file_line_text"><span class="pygments-cm">/* If we can get the size of the file up-front, and it's reasonably small,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1121">
<td class="vc_file_line_number">1121</td>

<td class="vc_file_line_text"><span class="pygments-cm"> * read it in one gulp and delegate to ...FromString() instead.  Much quicker</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1122">
<td class="vc_file_line_number">1122</td>

<td class="vc_file_line_text"><span class="pygments-cm"> * than reading a byte at a time from file; speeds .pyc imports.</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1123">
<td class="vc_file_line_number">1123</td>

<td class="vc_file_line_text"><span class="pygments-cm"> * CAUTION:  since this may read the entire remainder of the file, don't</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1124">
<td class="vc_file_line_number">1124</td>

<td class="vc_file_line_text"><span class="pygments-cm"> * call it unless you know you're done with the file.</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1125">
<td class="vc_file_line_number">1125</td>

<td class="vc_file_line_text"><span class="pygments-cm"> */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1126">
<td class="vc_file_line_number">1126</td>

<td class="vc_file_line_text"><span class="pygments-n">PyObject</span> <span class="pygments-o">*</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1127">
<td class="vc_file_line_number">1127</td>

<td class="vc_file_line_text"><span class="pygments-nf">PyMarshal_ReadLastObjectFromFile</span><span class="pygments-p">(</span><span class="pygments-kt">FILE</span> <span class="pygments-o">*</span><span class="pygments-n">fp</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1128">
<td class="vc_file_line_number">1128</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1129">
<td class="vc_file_line_number">1129</td>

<td class="vc_file_line_text"><span class="pygments-cm">/* REASONABLE_FILE_LIMIT is by defn something big enough for Tkinter.pyc. */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1130">
<td class="vc_file_line_number">1130</td>

<td class="vc_file_line_text"><span class="pygments-cp">#define REASONABLE_FILE_LIMIT (1L &lt;&lt; 18)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1131">
<td class="vc_file_line_number">1131</td>

<td class="vc_file_line_text"><span class="pygments-cp">#ifdef HAVE_FSTAT</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1132">
<td class="vc_file_line_number">1132</td>

<td class="vc_file_line_text">    <span class="pygments-kt">off_t</span> <span class="pygments-n">filesize</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1133">
<td class="vc_file_line_number">1133</td>

<td class="vc_file_line_text">    <span class="pygments-n">filesize</span> <span class="pygments-o">=</span> <span class="pygments-n">getfilesize</span><span class="pygments-p">(</span><span class="pygments-n">fp</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1134">
<td class="vc_file_line_number">1134</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">filesize</span> <span class="pygments-o">&gt;</span> <span class="pygments-mi">0</span> <span class="pygments-o">&amp;&amp;</span> <span class="pygments-n">filesize</span> <span class="pygments-o">&lt;=</span> <span class="pygments-n">REASONABLE_FILE_LIMIT</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1135">
<td class="vc_file_line_number">1135</td>

<td class="vc_file_line_text">        <span class="pygments-kt">char</span><span class="pygments-o">*</span> <span class="pygments-n">pBuf</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-kt">char</span> <span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">PyMem_MALLOC</span><span class="pygments-p">(</span><span class="pygments-n">filesize</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1136">
<td class="vc_file_line_number">1136</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">pBuf</span> <span class="pygments-o">!=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1137">
<td class="vc_file_line_number">1137</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyObject</span><span class="pygments-o">*</span> <span class="pygments-n">v</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1138">
<td class="vc_file_line_number">1138</td>

<td class="vc_file_line_text">            <span class="pygments-kt">size_t</span> <span class="pygments-n">n</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1139">
<td class="vc_file_line_number">1139</td>

<td class="vc_file_line_text">            <span class="pygments-cm">/* filesize must fit into an int, because it</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1140">
<td class="vc_file_line_number">1140</td>

<td class="vc_file_line_text"><span class="pygments-cm">               is smaller than REASONABLE_FILE_LIMIT */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1141">
<td class="vc_file_line_number">1141</td>

<td class="vc_file_line_text">            <span class="pygments-n">n</span> <span class="pygments-o">=</span> <span class="pygments-n">fread</span><span class="pygments-p">(</span><span class="pygments-n">pBuf</span><span class="pygments-p">,</span> <span class="pygments-mi">1</span><span class="pygments-p">,</span> <span class="pygments-p">(</span><span class="pygments-kt">int</span><span class="pygments-p">)</span><span class="pygments-n">filesize</span><span class="pygments-p">,</span> <span class="pygments-n">fp</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1142">
<td class="vc_file_line_number">1142</td>

<td class="vc_file_line_text">            <span class="pygments-n">v</span> <span class="pygments-o">=</span> <span class="pygments-n">PyMarshal_ReadObjectFromString</span><span class="pygments-p">(</span><span class="pygments-n">pBuf</span><span class="pygments-p">,</span> <span class="pygments-n">n</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1143">
<td class="vc_file_line_number">1143</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyMem_FREE</span><span class="pygments-p">(</span><span class="pygments-n">pBuf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1144">
<td class="vc_file_line_number">1144</td>

<td class="vc_file_line_text">            <span class="pygments-k">return</span> <span class="pygments-n">v</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1145">
<td class="vc_file_line_number">1145</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1146">
<td class="vc_file_line_number">1146</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1147">
<td class="vc_file_line_number">1147</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1148">
<td class="vc_file_line_number">1148</td>

<td class="vc_file_line_text"><span class="pygments-cp">#endif</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1149">
<td class="vc_file_line_number">1149</td>

<td class="vc_file_line_text">    <span class="pygments-cm">/* We don't have fstat, or we do but the file is larger than</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1150">
<td class="vc_file_line_number">1150</td>

<td class="vc_file_line_text"><span class="pygments-cm">     * REASONABLE_FILE_LIMIT or malloc failed -- read a byte at a time.</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1151">
<td class="vc_file_line_number">1151</td>

<td class="vc_file_line_text"><span class="pygments-cm">     */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1152">
<td class="vc_file_line_number">1152</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">PyMarshal_ReadObjectFromFile</span><span class="pygments-p">(</span><span class="pygments-n">fp</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1153">
<td class="vc_file_line_number">1153</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1154">
<td class="vc_file_line_number">1154</td>

<td class="vc_file_line_text"><span class="pygments-cp">#undef REASONABLE_FILE_LIMIT</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1155">
<td class="vc_file_line_number">1155</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1156">
<td class="vc_file_line_number">1156</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1157">
<td class="vc_file_line_number">1157</td>

<td class="vc_file_line_text"><span class="pygments-n">PyObject</span> <span class="pygments-o">*</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1158">
<td class="vc_file_line_number">1158</td>

<td class="vc_file_line_text"><span class="pygments-nf">PyMarshal_ReadObjectFromFile</span><span class="pygments-p">(</span><span class="pygments-kt">FILE</span> <span class="pygments-o">*</span><span class="pygments-n">fp</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1159">
<td class="vc_file_line_number">1159</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1160">
<td class="vc_file_line_number">1160</td>

<td class="vc_file_line_text">    <span class="pygments-n">RFILE</span> <span class="pygments-n">rf</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1161">
<td class="vc_file_line_number">1161</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">result</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1162">
<td class="vc_file_line_number">1162</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">fp</span> <span class="pygments-o">=</span> <span class="pygments-n">fp</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1163">
<td class="vc_file_line_number">1163</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span> <span class="pygments-o">=</span> <span class="pygments-n">PyList_New</span><span class="pygments-p">(</span><span class="pygments-mi">0</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1164">
<td class="vc_file_line_number">1164</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">depth</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1165">
<td class="vc_file_line_number">1165</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">ptr</span> <span class="pygments-o">=</span> <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">end</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1166">
<td class="vc_file_line_number">1166</td>

<td class="vc_file_line_text">    <span class="pygments-n">result</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-o">&amp;</span><span class="pygments-n">rf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1167">
<td class="vc_file_line_number">1167</td>

<td class="vc_file_line_text">    <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1168">
<td class="vc_file_line_number">1168</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">result</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1169">
<td class="vc_file_line_number">1169</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1170">
<td class="vc_file_line_number">1170</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1171">
<td class="vc_file_line_number">1171</td>

<td class="vc_file_line_text"><span class="pygments-n">PyObject</span> <span class="pygments-o">*</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1172">
<td class="vc_file_line_number">1172</td>

<td class="vc_file_line_text"><span class="pygments-nf">PyMarshal_ReadObjectFromString</span><span class="pygments-p">(</span><span class="pygments-kt">char</span> <span class="pygments-o">*</span><span class="pygments-n">str</span><span class="pygments-p">,</span> <span class="pygments-n">Py_ssize_t</span> <span class="pygments-n">len</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1173">
<td class="vc_file_line_number">1173</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1174">
<td class="vc_file_line_number">1174</td>

<td class="vc_file_line_text">    <span class="pygments-n">RFILE</span> <span class="pygments-n">rf</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1175">
<td class="vc_file_line_number">1175</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">result</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1176">
<td class="vc_file_line_number">1176</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">fp</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1177">
<td class="vc_file_line_number">1177</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">ptr</span> <span class="pygments-o">=</span> <span class="pygments-n">str</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1178">
<td class="vc_file_line_number">1178</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">end</span> <span class="pygments-o">=</span> <span class="pygments-n">str</span> <span class="pygments-o">+</span> <span class="pygments-n">len</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1179">
<td class="vc_file_line_number">1179</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span> <span class="pygments-o">=</span> <span class="pygments-n">PyList_New</span><span class="pygments-p">(</span><span class="pygments-mi">0</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1180">
<td class="vc_file_line_number">1180</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">depth</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1181">
<td class="vc_file_line_number">1181</td>

<td class="vc_file_line_text">    <span class="pygments-n">result</span> <span class="pygments-o">=</span> <span class="pygments-n">r_object</span><span class="pygments-p">(</span><span class="pygments-o">&amp;</span><span class="pygments-n">rf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1182">
<td class="vc_file_line_number">1182</td>

<td class="vc_file_line_text">    <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1183">
<td class="vc_file_line_number">1183</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">result</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1184">
<td class="vc_file_line_number">1184</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1185">
<td class="vc_file_line_number">1185</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1186">
<td class="vc_file_line_number">1186</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-kt">void</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1187">
<td class="vc_file_line_number">1187</td>

<td class="vc_file_line_text"><span class="pygments-nf">set_error</span><span class="pygments-p">(</span><span class="pygments-kt">int</span> <span class="pygments-n">error</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1188">
<td class="vc_file_line_number">1188</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1189">
<td class="vc_file_line_number">1189</td>

<td class="vc_file_line_text">    <span class="pygments-k">switch</span> <span class="pygments-p">(</span><span class="pygments-n">error</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1190">
<td class="vc_file_line_number">1190</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">WFERR_NOMEMORY</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l1191">
<td class="vc_file_line_number">1191</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyErr_NoMemory</span><span class="pygments-p">();</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1192">
<td class="vc_file_line_number">1192</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1193">
<td class="vc_file_line_number">1193</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">WFERR_UNMARSHALLABLE</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l1194">
<td class="vc_file_line_number">1194</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_ValueError</span><span class="pygments-p">,</span> <span class="pygments-s">"unmarshallable object"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1195">
<td class="vc_file_line_number">1195</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1196">
<td class="vc_file_line_number">1196</td>

<td class="vc_file_line_text">    <span class="pygments-k">case</span> <span class="pygments-n">WFERR_NESTEDTOODEEP</span>:
</td>
</tr>




<tr class="vc_row_odd" id="l1197">
<td class="vc_file_line_number">1197</td>

<td class="vc_file_line_text">    <span class="pygments-nl">default:</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1198">
<td class="vc_file_line_number">1198</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_ValueError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1199">
<td class="vc_file_line_number">1199</td>

<td class="vc_file_line_text">            <span class="pygments-s">"object too deeply nested to marshal"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1200">
<td class="vc_file_line_number">1200</td>

<td class="vc_file_line_text">        <span class="pygments-k">break</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1201">
<td class="vc_file_line_number">1201</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1202">
<td class="vc_file_line_number">1202</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1203">
<td class="vc_file_line_number">1203</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1204">
<td class="vc_file_line_number">1204</td>

<td class="vc_file_line_text"><span class="pygments-n">PyObject</span> <span class="pygments-o">*</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1205">
<td class="vc_file_line_number">1205</td>

<td class="vc_file_line_text"><span class="pygments-nf">PyMarshal_WriteObjectToString</span><span class="pygments-p">(</span><span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-kt">int</span> <span class="pygments-n">version</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1206">
<td class="vc_file_line_number">1206</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1207">
<td class="vc_file_line_number">1207</td>

<td class="vc_file_line_text">    <span class="pygments-n">WFILE</span> <span class="pygments-n">wf</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1208">
<td class="vc_file_line_number">1208</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">fp</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1209">
<td class="vc_file_line_number">1209</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">str</span> <span class="pygments-o">=</span> <span class="pygments-n">PyString_FromStringAndSize</span><span class="pygments-p">((</span><span class="pygments-kt">char</span> <span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-nb">NULL</span><span class="pygments-p">,</span> <span class="pygments-mi">50</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1210">
<td class="vc_file_line_number">1210</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">str</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1211">
<td class="vc_file_line_number">1211</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1212">
<td class="vc_file_line_number">1212</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">ptr</span> <span class="pygments-o">=</span> <span class="pygments-n">PyString_AS_STRING</span><span class="pygments-p">((</span><span class="pygments-n">PyStringObject</span> <span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">str</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1213">
<td class="vc_file_line_number">1213</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">end</span> <span class="pygments-o">=</span> <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">ptr</span> <span class="pygments-o">+</span> <span class="pygments-n">PyString_Size</span><span class="pygments-p">(</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">str</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1214">
<td class="vc_file_line_number">1214</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_OK</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1215">
<td class="vc_file_line_number">1215</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">depth</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1216">
<td class="vc_file_line_number">1216</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">version</span> <span class="pygments-o">=</span> <span class="pygments-n">version</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1217">
<td class="vc_file_line_number">1217</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-n">version</span> <span class="pygments-o">&gt;</span> <span class="pygments-mi">0</span><span class="pygments-p">)</span> <span class="pygments-o">?</span> <span class="pygments-n">PyDict_New</span><span class="pygments-p">()</span> <span class="pygments-o">:</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1218">
<td class="vc_file_line_number">1218</td>

<td class="vc_file_line_text">    <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">wf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1219">
<td class="vc_file_line_number">1219</td>

<td class="vc_file_line_text">    <span class="pygments-n">Py_XDECREF</span><span class="pygments-p">(</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1220">
<td class="vc_file_line_number">1220</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">str</span> <span class="pygments-o">!=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1221">
<td class="vc_file_line_number">1221</td>

<td class="vc_file_line_text">        <span class="pygments-kt">char</span> <span class="pygments-o">*</span><span class="pygments-n">base</span> <span class="pygments-o">=</span> <span class="pygments-n">PyString_AS_STRING</span><span class="pygments-p">((</span><span class="pygments-n">PyStringObject</span> <span class="pygments-o">*</span><span class="pygments-p">)</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">str</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1222">
<td class="vc_file_line_number">1222</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">ptr</span> <span class="pygments-o">-</span> <span class="pygments-n">base</span> <span class="pygments-o">&gt;</span> <span class="pygments-n">PY_SSIZE_T_MAX</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1223">
<td class="vc_file_line_number">1223</td>

<td class="vc_file_line_text">            <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">str</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1224">
<td class="vc_file_line_number">1224</td>

<td class="vc_file_line_text">            <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_OverflowError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1225">
<td class="vc_file_line_number">1225</td>

<td class="vc_file_line_text">                            <span class="pygments-s">"too much marshall data for a string"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1226">
<td class="vc_file_line_number">1226</td>

<td class="vc_file_line_text">            <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1227">
<td class="vc_file_line_number">1227</td>

<td class="vc_file_line_text">        <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1228">
<td class="vc_file_line_number">1228</td>

<td class="vc_file_line_text">        <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">_PyString_Resize</span><span class="pygments-p">(</span><span class="pygments-o">&amp;</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">str</span><span class="pygments-p">,</span> <span class="pygments-p">(</span><span class="pygments-n">Py_ssize_t</span><span class="pygments-p">)(</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">ptr</span> <span class="pygments-o">-</span> <span class="pygments-n">base</span><span class="pygments-p">)))</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1229">
<td class="vc_file_line_number">1229</td>

<td class="vc_file_line_text">            <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1230">
<td class="vc_file_line_number">1230</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1231">
<td class="vc_file_line_number">1231</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">error</span> <span class="pygments-o">!=</span> <span class="pygments-n">WFERR_OK</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1232">
<td class="vc_file_line_number">1232</td>

<td class="vc_file_line_text">        <span class="pygments-n">Py_XDECREF</span><span class="pygments-p">(</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">str</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1233">
<td class="vc_file_line_number">1233</td>

<td class="vc_file_line_text">        <span class="pygments-n">set_error</span><span class="pygments-p">(</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">error</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1234">
<td class="vc_file_line_number">1234</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1235">
<td class="vc_file_line_number">1235</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1236">
<td class="vc_file_line_number">1236</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">str</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1237">
<td class="vc_file_line_number">1237</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1238">
<td class="vc_file_line_number">1238</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1239">
<td class="vc_file_line_number">1239</td>

<td class="vc_file_line_text"><span class="pygments-cm">/* And an interface for Python programs... */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1240">
<td class="vc_file_line_number">1240</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1241">
<td class="vc_file_line_number">1241</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1242">
<td class="vc_file_line_number">1242</td>

<td class="vc_file_line_text"><span class="pygments-nf">marshal_dump</span><span class="pygments-p">(</span><span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">self</span><span class="pygments-p">,</span> <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">args</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1243">
<td class="vc_file_line_number">1243</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1244">
<td class="vc_file_line_number">1244</td>

<td class="vc_file_line_text">    <span class="pygments-n">WFILE</span> <span class="pygments-n">wf</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1245">
<td class="vc_file_line_number">1245</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">x</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1246">
<td class="vc_file_line_number">1246</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">f</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1247">
<td class="vc_file_line_number">1247</td>

<td class="vc_file_line_text">    <span class="pygments-kt">int</span> <span class="pygments-n">version</span> <span class="pygments-o">=</span> <span class="pygments-n">Py_MARSHAL_VERSION</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1248">
<td class="vc_file_line_number">1248</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-o">!</span><span class="pygments-n">PyArg_ParseTuple</span><span class="pygments-p">(</span><span class="pygments-n">args</span><span class="pygments-p">,</span> <span class="pygments-s">"OO|i:dump"</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">f</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">version</span><span class="pygments-p">))</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1249">
<td class="vc_file_line_number">1249</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1250">
<td class="vc_file_line_number">1250</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-o">!</span><span class="pygments-n">PyFile_Check</span><span class="pygments-p">(</span><span class="pygments-n">f</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1251">
<td class="vc_file_line_number">1251</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_TypeError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1252">
<td class="vc_file_line_number">1252</td>

<td class="vc_file_line_text">                        <span class="pygments-s">"marshal.dump() 2nd arg must be file"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1253">
<td class="vc_file_line_number">1253</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1254">
<td class="vc_file_line_number">1254</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1255">
<td class="vc_file_line_number">1255</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">fp</span> <span class="pygments-o">=</span> <span class="pygments-n">PyFile_AsFile</span><span class="pygments-p">(</span><span class="pygments-n">f</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1256">
<td class="vc_file_line_number">1256</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">str</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1257">
<td class="vc_file_line_number">1257</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">ptr</span> <span class="pygments-o">=</span> <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">end</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1258">
<td class="vc_file_line_number">1258</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">error</span> <span class="pygments-o">=</span> <span class="pygments-n">WFERR_OK</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1259">
<td class="vc_file_line_number">1259</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">depth</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1260">
<td class="vc_file_line_number">1260</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span> <span class="pygments-o">=</span> <span class="pygments-p">(</span><span class="pygments-n">version</span> <span class="pygments-o">&gt;</span> <span class="pygments-mi">0</span><span class="pygments-p">)</span> <span class="pygments-o">?</span> <span class="pygments-n">PyDict_New</span><span class="pygments-p">()</span> <span class="pygments-o">:</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1261">
<td class="vc_file_line_number">1261</td>

<td class="vc_file_line_text">    <span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">version</span> <span class="pygments-o">=</span> <span class="pygments-n">version</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1262">
<td class="vc_file_line_number">1262</td>

<td class="vc_file_line_text">    <span class="pygments-n">w_object</span><span class="pygments-p">(</span><span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">wf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1263">
<td class="vc_file_line_number">1263</td>

<td class="vc_file_line_text">    <span class="pygments-n">Py_XDECREF</span><span class="pygments-p">(</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1264">
<td class="vc_file_line_number">1264</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">error</span> <span class="pygments-o">!=</span> <span class="pygments-n">WFERR_OK</span><span class="pygments-p">)</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1265">
<td class="vc_file_line_number">1265</td>

<td class="vc_file_line_text">        <span class="pygments-n">set_error</span><span class="pygments-p">(</span><span class="pygments-n">wf</span><span class="pygments-p">.</span><span class="pygments-n">error</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1266">
<td class="vc_file_line_number">1266</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1267">
<td class="vc_file_line_number">1267</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1268">
<td class="vc_file_line_number">1268</td>

<td class="vc_file_line_text">    <span class="pygments-n">Py_INCREF</span><span class="pygments-p">(</span><span class="pygments-n">Py_None</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1269">
<td class="vc_file_line_number">1269</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">Py_None</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1270">
<td class="vc_file_line_number">1270</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1271">
<td class="vc_file_line_number">1271</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1272">
<td class="vc_file_line_number">1272</td>

<td class="vc_file_line_text"><span class="pygments-n">PyDoc_STRVAR</span><span class="pygments-p">(</span><span class="pygments-n">dump_doc</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1273">
<td class="vc_file_line_number">1273</td>

<td class="vc_file_line_text"><span class="pygments-s">"dump(value, file[, version])</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1274">
<td class="vc_file_line_number">1274</td>

<td class="vc_file_line_text"><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1275">
<td class="vc_file_line_number">1275</td>

<td class="vc_file_line_text"><span class="pygments-s">Write the value on the open file. The value must be a supported type.</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1276">
<td class="vc_file_line_number">1276</td>

<td class="vc_file_line_text"><span class="pygments-s">The file must be an open file object such as sys.stdout or returned by</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1277">
<td class="vc_file_line_number">1277</td>

<td class="vc_file_line_text"><span class="pygments-s">open() or os.popen(). It must be opened in binary mode ('wb' or 'w+b').</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1278">
<td class="vc_file_line_number">1278</td>

<td class="vc_file_line_text"><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1279">
<td class="vc_file_line_number">1279</td>

<td class="vc_file_line_text"><span class="pygments-s">If the value has (or contains an object that has) an unsupported type, a</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1280">
<td class="vc_file_line_number">1280</td>

<td class="vc_file_line_text"><span class="pygments-s">ValueError exception is raised — but garbage data will also be written</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1281">
<td class="vc_file_line_number">1281</td>

<td class="vc_file_line_text"><span class="pygments-s">to the file. The object will not be properly read back by load()</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1282">
<td class="vc_file_line_number">1282</td>

<td class="vc_file_line_text"><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1283">
<td class="vc_file_line_number">1283</td>

<td class="vc_file_line_text"><span class="pygments-s">New in version 2.4: The version argument indicates the data format that</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1284">
<td class="vc_file_line_number">1284</td>

<td class="vc_file_line_text"><span class="pygments-s">dump should use."</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1285">
<td class="vc_file_line_number">1285</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1286">
<td class="vc_file_line_number">1286</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1287">
<td class="vc_file_line_number">1287</td>

<td class="vc_file_line_text"><span class="pygments-nf">marshal_load</span><span class="pygments-p">(</span><span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">self</span><span class="pygments-p">,</span> <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">f</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1288">
<td class="vc_file_line_number">1288</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1289">
<td class="vc_file_line_number">1289</td>

<td class="vc_file_line_text">    <span class="pygments-n">RFILE</span> <span class="pygments-n">rf</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1290">
<td class="vc_file_line_number">1290</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">result</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1291">
<td class="vc_file_line_number">1291</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-o">!</span><span class="pygments-n">PyFile_Check</span><span class="pygments-p">(</span><span class="pygments-n">f</span><span class="pygments-p">))</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1292">
<td class="vc_file_line_number">1292</td>

<td class="vc_file_line_text">        <span class="pygments-n">PyErr_SetString</span><span class="pygments-p">(</span><span class="pygments-n">PyExc_TypeError</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1293">
<td class="vc_file_line_number">1293</td>

<td class="vc_file_line_text">                        <span class="pygments-s">"marshal.load() arg must be file"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1294">
<td class="vc_file_line_number">1294</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1295">
<td class="vc_file_line_number">1295</td>

<td class="vc_file_line_text">    <span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1296">
<td class="vc_file_line_number">1296</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">fp</span> <span class="pygments-o">=</span> <span class="pygments-n">PyFile_AsFile</span><span class="pygments-p">(</span><span class="pygments-n">f</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1297">
<td class="vc_file_line_number">1297</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span> <span class="pygments-o">=</span> <span class="pygments-n">PyList_New</span><span class="pygments-p">(</span><span class="pygments-mi">0</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1298">
<td class="vc_file_line_number">1298</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">depth</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1299">
<td class="vc_file_line_number">1299</td>

<td class="vc_file_line_text">    <span class="pygments-n">result</span> <span class="pygments-o">=</span> <span class="pygments-n">read_object</span><span class="pygments-p">(</span><span class="pygments-o">&amp;</span><span class="pygments-n">rf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1300">
<td class="vc_file_line_number">1300</td>

<td class="vc_file_line_text">    <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1301">
<td class="vc_file_line_number">1301</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">result</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1302">
<td class="vc_file_line_number">1302</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1303">
<td class="vc_file_line_number">1303</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1304">
<td class="vc_file_line_number">1304</td>

<td class="vc_file_line_text"><span class="pygments-n">PyDoc_STRVAR</span><span class="pygments-p">(</span><span class="pygments-n">load_doc</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1305">
<td class="vc_file_line_number">1305</td>

<td class="vc_file_line_text"><span class="pygments-s">"load(file)</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1306">
<td class="vc_file_line_number">1306</td>

<td class="vc_file_line_text"><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1307">
<td class="vc_file_line_number">1307</td>

<td class="vc_file_line_text"><span class="pygments-s">Read one value from the open file and return it. If no valid value is</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1308">
<td class="vc_file_line_number">1308</td>

<td class="vc_file_line_text"><span class="pygments-s">read (e.g. because the data has a different Python version’s</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1309">
<td class="vc_file_line_number">1309</td>

<td class="vc_file_line_text"><span class="pygments-s">incompatible marshal format), raise EOFError, ValueError or TypeError.</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1310">
<td class="vc_file_line_number">1310</td>

<td class="vc_file_line_text"><span class="pygments-s">The file must be an open file object opened in binary mode ('rb' or</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1311">
<td class="vc_file_line_number">1311</td>

<td class="vc_file_line_text"><span class="pygments-s">'r+b').</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1312">
<td class="vc_file_line_number">1312</td>

<td class="vc_file_line_text"><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1313">
<td class="vc_file_line_number">1313</td>

<td class="vc_file_line_text"><span class="pygments-s">Note: If an object containing an unsupported type was marshalled with</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1314">
<td class="vc_file_line_number">1314</td>

<td class="vc_file_line_text"><span class="pygments-s">dump(), load() will substitute None for the unmarshallable type."</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1315">
<td class="vc_file_line_number">1315</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1316">
<td class="vc_file_line_number">1316</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1317">
<td class="vc_file_line_number">1317</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1318">
<td class="vc_file_line_number">1318</td>

<td class="vc_file_line_text"><span class="pygments-nf">marshal_dumps</span><span class="pygments-p">(</span><span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">self</span><span class="pygments-p">,</span> <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">args</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1319">
<td class="vc_file_line_number">1319</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1320">
<td class="vc_file_line_number">1320</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">x</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1321">
<td class="vc_file_line_number">1321</td>

<td class="vc_file_line_text">    <span class="pygments-kt">int</span> <span class="pygments-n">version</span> <span class="pygments-o">=</span> <span class="pygments-n">Py_MARSHAL_VERSION</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1322">
<td class="vc_file_line_number">1322</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-o">!</span><span class="pygments-n">PyArg_ParseTuple</span><span class="pygments-p">(</span><span class="pygments-n">args</span><span class="pygments-p">,</span> <span class="pygments-s">"O|i:dumps"</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">version</span><span class="pygments-p">))</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1323">
<td class="vc_file_line_number">1323</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1324">
<td class="vc_file_line_number">1324</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">PyMarshal_WriteObjectToString</span><span class="pygments-p">(</span><span class="pygments-n">x</span><span class="pygments-p">,</span> <span class="pygments-n">version</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1325">
<td class="vc_file_line_number">1325</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1326">
<td class="vc_file_line_number">1326</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1327">
<td class="vc_file_line_number">1327</td>

<td class="vc_file_line_text"><span class="pygments-n">PyDoc_STRVAR</span><span class="pygments-p">(</span><span class="pygments-n">dumps_doc</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1328">
<td class="vc_file_line_number">1328</td>

<td class="vc_file_line_text"><span class="pygments-s">"dumps(value[, version])</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1329">
<td class="vc_file_line_number">1329</td>

<td class="vc_file_line_text"><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1330">
<td class="vc_file_line_number">1330</td>

<td class="vc_file_line_text"><span class="pygments-s">Return the string that would be written to a file by dump(value, file).</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1331">
<td class="vc_file_line_number">1331</td>

<td class="vc_file_line_text"><span class="pygments-s">The value must be a supported type. Raise a ValueError exception if</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1332">
<td class="vc_file_line_number">1332</td>

<td class="vc_file_line_text"><span class="pygments-s">value has (or contains an object that has) an unsupported type.</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1333">
<td class="vc_file_line_number">1333</td>

<td class="vc_file_line_text"><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1334">
<td class="vc_file_line_number">1334</td>

<td class="vc_file_line_text"><span class="pygments-s">New in version 2.4: The version argument indicates the data format that</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1335">
<td class="vc_file_line_number">1335</td>

<td class="vc_file_line_text"><span class="pygments-s">dumps should use."</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1336">
<td class="vc_file_line_number">1336</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1337">
<td class="vc_file_line_number">1337</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1338">
<td class="vc_file_line_number">1338</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1339">
<td class="vc_file_line_number">1339</td>

<td class="vc_file_line_text"><span class="pygments-nf">marshal_loads</span><span class="pygments-p">(</span><span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">self</span><span class="pygments-p">,</span> <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">args</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1340">
<td class="vc_file_line_number">1340</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1341">
<td class="vc_file_line_number">1341</td>

<td class="vc_file_line_text">    <span class="pygments-n">RFILE</span> <span class="pygments-n">rf</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1342">
<td class="vc_file_line_number">1342</td>

<td class="vc_file_line_text">    <span class="pygments-kt">char</span> <span class="pygments-o">*</span><span class="pygments-n">s</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1343">
<td class="vc_file_line_number">1343</td>

<td class="vc_file_line_text">    <span class="pygments-n">Py_ssize_t</span> <span class="pygments-n">n</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1344">
<td class="vc_file_line_number">1344</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyObject</span><span class="pygments-o">*</span> <span class="pygments-n">result</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1345">
<td class="vc_file_line_number">1345</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-o">!</span><span class="pygments-n">PyArg_ParseTuple</span><span class="pygments-p">(</span><span class="pygments-n">args</span><span class="pygments-p">,</span> <span class="pygments-s">"s#:loads"</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">s</span><span class="pygments-p">,</span> <span class="pygments-o">&amp;</span><span class="pygments-n">n</span><span class="pygments-p">))</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1346">
<td class="vc_file_line_number">1346</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1347">
<td class="vc_file_line_number">1347</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">fp</span> <span class="pygments-o">=</span> <span class="pygments-nb">NULL</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1348">
<td class="vc_file_line_number">1348</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">ptr</span> <span class="pygments-o">=</span> <span class="pygments-n">s</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1349">
<td class="vc_file_line_number">1349</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">end</span> <span class="pygments-o">=</span> <span class="pygments-n">s</span> <span class="pygments-o">+</span> <span class="pygments-n">n</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1350">
<td class="vc_file_line_number">1350</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span> <span class="pygments-o">=</span> <span class="pygments-n">PyList_New</span><span class="pygments-p">(</span><span class="pygments-mi">0</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1351">
<td class="vc_file_line_number">1351</td>

<td class="vc_file_line_text">    <span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">depth</span> <span class="pygments-o">=</span> <span class="pygments-mi">0</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1352">
<td class="vc_file_line_number">1352</td>

<td class="vc_file_line_text">    <span class="pygments-n">result</span> <span class="pygments-o">=</span> <span class="pygments-n">read_object</span><span class="pygments-p">(</span><span class="pygments-o">&amp;</span><span class="pygments-n">rf</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1353">
<td class="vc_file_line_number">1353</td>

<td class="vc_file_line_text">    <span class="pygments-n">Py_DECREF</span><span class="pygments-p">(</span><span class="pygments-n">rf</span><span class="pygments-p">.</span><span class="pygments-n">strings</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1354">
<td class="vc_file_line_number">1354</td>

<td class="vc_file_line_text">    <span class="pygments-k">return</span> <span class="pygments-n">result</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1355">
<td class="vc_file_line_number">1355</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1356">
<td class="vc_file_line_number">1356</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1357">
<td class="vc_file_line_number">1357</td>

<td class="vc_file_line_text"><span class="pygments-n">PyDoc_STRVAR</span><span class="pygments-p">(</span><span class="pygments-n">loads_doc</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1358">
<td class="vc_file_line_number">1358</td>

<td class="vc_file_line_text"><span class="pygments-s">"loads(string)</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1359">
<td class="vc_file_line_number">1359</td>

<td class="vc_file_line_text"><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1360">
<td class="vc_file_line_number">1360</td>

<td class="vc_file_line_text"><span class="pygments-s">Convert the string to a value. If no valid value is found, raise</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1361">
<td class="vc_file_line_number">1361</td>

<td class="vc_file_line_text"><span class="pygments-s">EOFError, ValueError or TypeError. Extra characters in the string are</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1362">
<td class="vc_file_line_number">1362</td>

<td class="vc_file_line_text"><span class="pygments-s">ignored."</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1363">
<td class="vc_file_line_number">1363</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1364">
<td class="vc_file_line_number">1364</td>

<td class="vc_file_line_text"><span class="pygments-k">static</span> <span class="pygments-n">PyMethodDef</span> <span class="pygments-n">marshal_methods</span><span class="pygments-p">[]</span> <span class="pygments-o">=</span> <span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1365">
<td class="vc_file_line_number">1365</td>

<td class="vc_file_line_text">    <span class="pygments-p">{</span><span class="pygments-s">"dump"</span><span class="pygments-p">,</span>            <span class="pygments-n">marshal_dump</span><span class="pygments-p">,</span>   <span class="pygments-n">METH_VARARGS</span><span class="pygments-p">,</span>   <span class="pygments-n">dump_doc</span><span class="pygments-p">},</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1366">
<td class="vc_file_line_number">1366</td>

<td class="vc_file_line_text">    <span class="pygments-p">{</span><span class="pygments-s">"load"</span><span class="pygments-p">,</span>            <span class="pygments-n">marshal_load</span><span class="pygments-p">,</span>   <span class="pygments-n">METH_O</span><span class="pygments-p">,</span>         <span class="pygments-n">load_doc</span><span class="pygments-p">},</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1367">
<td class="vc_file_line_number">1367</td>

<td class="vc_file_line_text">    <span class="pygments-p">{</span><span class="pygments-s">"dumps"</span><span class="pygments-p">,</span>           <span class="pygments-n">marshal_dumps</span><span class="pygments-p">,</span>  <span class="pygments-n">METH_VARARGS</span><span class="pygments-p">,</span>   <span class="pygments-n">dumps_doc</span><span class="pygments-p">},</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1368">
<td class="vc_file_line_number">1368</td>

<td class="vc_file_line_text">    <span class="pygments-p">{</span><span class="pygments-s">"loads"</span><span class="pygments-p">,</span>           <span class="pygments-n">marshal_loads</span><span class="pygments-p">,</span>  <span class="pygments-n">METH_VARARGS</span><span class="pygments-p">,</span>   <span class="pygments-n">loads_doc</span><span class="pygments-p">},</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1369">
<td class="vc_file_line_number">1369</td>

<td class="vc_file_line_text">    <span class="pygments-p">{</span><span class="pygments-nb">NULL</span><span class="pygments-p">,</span>              <span class="pygments-nb">NULL</span><span class="pygments-p">}</span>           <span class="pygments-cm">/* sentinel */</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1370">
<td class="vc_file_line_number">1370</td>

<td class="vc_file_line_text"><span class="pygments-p">};</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1371">
<td class="vc_file_line_number">1371</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1372">
<td class="vc_file_line_number">1372</td>

<td class="vc_file_line_text"><span class="pygments-n">PyDoc_STRVAR</span><span class="pygments-p">(</span><span class="pygments-n">marshal_doc</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1373">
<td class="vc_file_line_number">1373</td>

<td class="vc_file_line_text"><span class="pygments-s">"This module contains functions that can read and write Python values in</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1374">
<td class="vc_file_line_number">1374</td>

<td class="vc_file_line_text"><span class="pygments-s">a binary format. The format is specific to Python, but independent of</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1375">
<td class="vc_file_line_number">1375</td>

<td class="vc_file_line_text"><span class="pygments-s">machine architecture issues.</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1376">
<td class="vc_file_line_number">1376</td>

<td class="vc_file_line_text"><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1377">
<td class="vc_file_line_number">1377</td>

<td class="vc_file_line_text"><span class="pygments-s">Not all Python object types are supported; in general, only objects</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1378">
<td class="vc_file_line_number">1378</td>

<td class="vc_file_line_text"><span class="pygments-s">whose value is independent from a particular invocation of Python can be</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1379">
<td class="vc_file_line_number">1379</td>

<td class="vc_file_line_text"><span class="pygments-s">written and read by this module. The following types are supported:</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1380">
<td class="vc_file_line_number">1380</td>

<td class="vc_file_line_text"><span class="pygments-s">None, integers, long integers, floating point numbers, strings, Unicode</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1381">
<td class="vc_file_line_number">1381</td>

<td class="vc_file_line_text"><span class="pygments-s">objects, tuples, lists, sets, dictionaries, and code objects, where it</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1382">
<td class="vc_file_line_number">1382</td>

<td class="vc_file_line_text"><span class="pygments-s">should be understood that tuples, lists and dictionaries are only</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1383">
<td class="vc_file_line_number">1383</td>

<td class="vc_file_line_text"><span class="pygments-s">supported as long as the values contained therein are themselves</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1384">
<td class="vc_file_line_number">1384</td>

<td class="vc_file_line_text"><span class="pygments-s">supported; and recursive lists and dictionaries should not be written</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1385">
<td class="vc_file_line_number">1385</td>

<td class="vc_file_line_text"><span class="pygments-s">(they will cause infinite loops).</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1386">
<td class="vc_file_line_number">1386</td>

<td class="vc_file_line_text"><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1387">
<td class="vc_file_line_number">1387</td>

<td class="vc_file_line_text"><span class="pygments-s">Variables:</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1388">
<td class="vc_file_line_number">1388</td>

<td class="vc_file_line_text"><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1389">
<td class="vc_file_line_number">1389</td>

<td class="vc_file_line_text"><span class="pygments-s">version -- indicates the format that the module uses. Version 0 is the</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1390">
<td class="vc_file_line_number">1390</td>

<td class="vc_file_line_text"><span class="pygments-s">    historical format, version 1 (added in Python 2.4) shares interned</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1391">
<td class="vc_file_line_number">1391</td>

<td class="vc_file_line_text"><span class="pygments-s">    strings and version 2 (added in Python 2.5) uses a binary format for</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1392">
<td class="vc_file_line_number">1392</td>

<td class="vc_file_line_text"><span class="pygments-s">    floating point numbers. (New in version 2.4)</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1393">
<td class="vc_file_line_number">1393</td>

<td class="vc_file_line_text"><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1394">
<td class="vc_file_line_number">1394</td>

<td class="vc_file_line_text"><span class="pygments-s">Functions:</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1395">
<td class="vc_file_line_number">1395</td>

<td class="vc_file_line_text"><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1396">
<td class="vc_file_line_number">1396</td>

<td class="vc_file_line_text"><span class="pygments-s">dump() -- write value to a file</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1397">
<td class="vc_file_line_number">1397</td>

<td class="vc_file_line_text"><span class="pygments-s">load() -- read value from a file</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1398">
<td class="vc_file_line_number">1398</td>

<td class="vc_file_line_text"><span class="pygments-s">dumps() -- write value to a string</span><span class="pygments-se">\n</span><span class="pygments-s">\</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1399">
<td class="vc_file_line_number">1399</td>

<td class="vc_file_line_text"><span class="pygments-s">loads() -- read value from a string"</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1400">
<td class="vc_file_line_number">1400</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1401">
<td class="vc_file_line_number">1401</td>

<td class="vc_file_line_text">
</td>
</tr>




<tr class="vc_row_odd" id="l1402">
<td class="vc_file_line_number">1402</td>

<td class="vc_file_line_text"><span class="pygments-n">PyMODINIT_FUNC</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1403">
<td class="vc_file_line_number">1403</td>

<td class="vc_file_line_text"><span class="pygments-nf">PyMarshal_Init</span><span class="pygments-p">(</span><span class="pygments-kt">void</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1404">
<td class="vc_file_line_number">1404</td>

<td class="vc_file_line_text"><span class="pygments-p">{</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1405">
<td class="vc_file_line_number">1405</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyObject</span> <span class="pygments-o">*</span><span class="pygments-n">mod</span> <span class="pygments-o">=</span> <span class="pygments-n">Py_InitModule3</span><span class="pygments-p">(</span><span class="pygments-s">"marshal"</span><span class="pygments-p">,</span> <span class="pygments-n">marshal_methods</span><span class="pygments-p">,</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1406">
<td class="vc_file_line_number">1406</td>

<td class="vc_file_line_text">        <span class="pygments-n">marshal_doc</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1407">
<td class="vc_file_line_number">1407</td>

<td class="vc_file_line_text">    <span class="pygments-k">if</span> <span class="pygments-p">(</span><span class="pygments-n">mod</span> <span class="pygments-o">==</span> <span class="pygments-nb">NULL</span><span class="pygments-p">)</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1408">
<td class="vc_file_line_number">1408</td>

<td class="vc_file_line_text">        <span class="pygments-k">return</span><span class="pygments-p">;</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1409">
<td class="vc_file_line_number">1409</td>

<td class="vc_file_line_text">    <span class="pygments-n">PyModule_AddIntConstant</span><span class="pygments-p">(</span><span class="pygments-n">mod</span><span class="pygments-p">,</span> <span class="pygments-s">"version"</span><span class="pygments-p">,</span> <span class="pygments-n">Py_MARSHAL_VERSION</span><span class="pygments-p">);</span>
</td>
</tr>




<tr class="vc_row_odd" id="l1410">
<td class="vc_file_line_number">1410</td>

<td class="vc_file_line_text"><span class="pygments-p">}</span>
</td>
</tr>


</tbody></table>
</div>



<hr>
<div class="vc_properties">
<h2>Properties</h2>
<table class="auto" cellpadding="2" cellspacing="1">
<thead>
<tr>
<th class="vc_header_sort">Name</th>
<th class="vc_header">Value</th>
</tr>
</thead>
<tbody>

<tr class="vc_row_even">
<td><strong>svn:eol-style</strong></td>

<td style="white-space: pre;">native</td>

</tr>

<tr class="vc_row_odd">
<td><strong>svn:keywords</strong></td>

<td style="white-space: pre;">Author Date Id Revision</td>

</tr>

</tbody>
</table>
</div>



<hr>
<table>
<tbody><tr>
<td><address><a href="mailto:webmaster@python.org">webmaster@python.org</a></address></td>
<td style="text-align: right;"><strong><a href="http://svn.python.org/viewvc/help_rootview.html">ViewVC Help</a></strong></td>
</tr>
<tr>
<td>Powered by <a href="http://viewvc.tigris.org/">ViewVC 1.1.5</a></td>
<td style="text-align: right;">&nbsp;</td>
</tr>
</tbody></table>



</body></html>