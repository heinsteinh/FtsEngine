



<!DOCTYPE html>
<html>
<head>
 <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" >
 <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" >
 
 <meta name="ROBOTS" content="NOARCHIVE">
 
 <link rel="icon" type="image/vnd.microsoft.icon" href="http://www.gstatic.com/codesite/ph/images/phosting.ico">
 
 
 <script type="text/javascript">
 
 
 
 
 var codesite_token = "X1eqbq8kTawg_LR6OVnbehjqPTI:1398845685991";
 
 
 var CS_env = {"projectHomeUrl": "/p/gamekit", "loggedInUserEmail": "heinsteinh@gmail.com", "token": "X1eqbq8kTawg_LR6OVnbehjqPTI:1398845685991", "domainName": null, "profileUrl": "/u/112241180151938862863/", "projectName": "gamekit", "assetVersionPath": "http://www.gstatic.com/codesite/ph/3427079965498762429", "relativeBaseUrl": "", "assetHostPath": "http://www.gstatic.com/codesite/ph"};
 var _gaq = _gaq || [];
 _gaq.push(
 ['siteTracker._setAccount', 'UA-18071-1'],
 ['siteTracker._trackPageview']);
 
 _gaq.push(
 ['projectTracker._setAccount', 'UA-807495-4'],
 ['projectTracker._trackPageview']);
 
 (function() {
 var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
 ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
 (document.getElementsByTagName('head')[0] || document.getElementsByTagName('body')[0]).appendChild(ga);
 })();
 
 </script>
 
 
 <title>ShaderLang.h - 
 gamekit -
 
 
 A cross-platform 3D game engine using Ogre or Irrlicht and Bullet for Windows, Linux, Mac, Android and iPhone - Google Project Hosting
 </title>
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/3427079965498762429/css/core.css">
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/3427079965498762429/css/ph_detail.css" >
 
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/3427079965498762429/css/d_sb.css" >
 
 
 
<!--[if IE]>
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/3427079965498762429/css/d_ie.css" >
<![endif]-->
 <style type="text/css">
 .menuIcon.off { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -42px }
 .menuIcon.on { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -28px }
 .menuIcon.down { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 0; }
 
 
 
  tr.inline_comment {
 background: #fff;
 vertical-align: top;
 }
 div.draft, div.published {
 padding: .3em;
 border: 1px solid #999; 
 margin-bottom: .1em;
 font-family: arial, sans-serif;
 max-width: 60em;
 }
 div.draft {
 background: #ffa;
 } 
 div.published {
 background: #e5ecf9;
 }
 div.published .body, div.draft .body {
 padding: .5em .1em .1em .1em;
 max-width: 60em;
 white-space: pre-wrap;
 white-space: -moz-pre-wrap;
 white-space: -pre-wrap;
 white-space: -o-pre-wrap;
 word-wrap: break-word;
 font-size: 1em;
 }
 div.draft .actions {
 margin-left: 1em;
 font-size: 90%;
 }
 div.draft form {
 padding: .5em .5em .5em 0;
 }
 div.draft textarea, div.published textarea {
 width: 95%;
 height: 10em;
 font-family: arial, sans-serif;
 margin-bottom: .5em;
 }

 
 .nocursor, .nocursor td, .cursor_hidden, .cursor_hidden td {
 background-color: white;
 height: 2px;
 }
 .cursor, .cursor td {
 background-color: darkblue;
 height: 2px;
 display: '';
 }
 
 
.list {
 border: 1px solid white;
 border-bottom: 0;
}

 
 </style>
</head>
<body class="t4">
<script type="text/javascript">
 window.___gcfg = {lang: 'en'};
 (function() 
 {var po = document.createElement("script");
 po.type = "text/javascript"; po.async = true;po.src = "https://apis.google.com/js/plusone.js";
 var s = document.getElementsByTagName("script")[0];
 s.parentNode.insertBefore(po, s);
 })();
</script>
<div class="headbg">

 <div id="gaia">
 

 <span>
 
 
 
 <a href="#" id="multilogin-dropdown" onclick="return false;"
 ><u><b>heinsteinh@gmail.com</b></u> <small>&#9660;</small></a>
 
 
 | <a href="/u/112241180151938862863/" id="projects-dropdown" onclick="return false;"
 ><u>My favorites</u> <small>&#9660;</small></a>
 | <a href="/u/112241180151938862863/" onclick="_CS_click('/gb/ph/profile');"
 title="Profile, Updates, and Settings"
 ><u>Profile</u></a>
 | <a href="https://www.google.com/accounts/Logout?continue=http%3A%2F%2Fcode.google.com%2Fp%2Fgamekit%2Fsource%2Fbrowse%2Ftrunk%2FDependencies%2FWin32%2Fgles2%2Finclude%2FGLSLANG%2FShaderLang.h%3Fr%3D887" 
 onclick="_CS_click('/gb/ph/signout');"
 ><u>Sign out</u></a>
 
 </span>

 </div>

 <div class="gbh" style="left: 0pt;"></div>
 <div class="gbh" style="right: 0pt;"></div>
 
 
 <div style="height: 1px"></div>
<!--[if lte IE 7]>
<div style="text-align:center;">
Your version of Internet Explorer is not supported. Try a browser that
contributes to open source, such as <a href="http://www.firefox.com">Firefox</a>,
<a href="http://www.google.com/chrome">Google Chrome</a>, or
<a href="http://code.google.com/chrome/chromeframe/">Google Chrome Frame</a>.
</div>
<![endif]-->



 <table style="padding:0px; margin: 0px 0px 10px 0px; width:100%" cellpadding="0" cellspacing="0"
 itemscope itemtype="http://schema.org/CreativeWork">
 <tr style="height: 58px;">
 
 
 
 <td id="plogo">
 <link itemprop="url" href="/p/gamekit">
 <a href="/p/gamekit/">
 
 
 <img src="/p/gamekit/logo?cct=1365483715"
 alt="Logo" itemprop="image">
 
 </a>
 </td>
 
 <td style="padding-left: 0.5em">
 
 <div id="pname">
 <a href="/p/gamekit/"><span itemprop="name">gamekit</span></a>
 </div>
 
 <div id="psum">
 <a id="project_summary_link"
 href="/p/gamekit/"><span itemprop="description">A cross-platform 3D game engine using Ogre or Irrlicht and Bullet for Windows, Linux, Mac, Android and iPhone</span></a>
 
 </div>
 
 
 </td>
 <td style="white-space:nowrap;text-align:right; vertical-align:bottom;">
 
 <form action="/hosting/search">
 <input size="30" name="q" value="" type="text">
 
 <input type="submit" name="projectsearch" value="Search projects" >
 </form>
 
 </tr>
 </table>

</div>

 
<div id="mt" class="gtb"> 
 <a href="/p/gamekit/" class="tab ">Project&nbsp;Home</a>
 
 
 
 
 <a href="/p/gamekit/downloads/list" class="tab ">Downloads</a>
 
 
 
 
 
 <a href="/p/gamekit/w/list" class="tab ">Wiki</a>
 
 
 
 
 
 <a href="/p/gamekit/issues/list"
 class="tab ">Issues</a>
 
 
 
 
 
 <a href="/p/gamekit/source/checkout"
 class="tab active">Source</a>
 
 
 
 
 
 
 
 
 <div class=gtbc></div>
</div>
<table cellspacing="0" cellpadding="0" width="100%" align="center" border="0" class="st">
 <tr>
 
 
 
 
 
 
 <td class="subt">
 <div class="st2">
 <div class="isf">
 
 


 <span class="inst1"><a href="/p/gamekit/source/checkout">Checkout</a></span> &nbsp;
 <span class="inst2"><a href="/p/gamekit/source/browse/">Browse</a></span> &nbsp;
 <span class="inst3"><a href="/p/gamekit/source/list">Changes</a></span> &nbsp;
 
 
 
 
 
 
 
 </form>
 <script type="text/javascript">
 
 function codesearchQuery(form) {
 var query = document.getElementById('q').value;
 if (query) { form.action += '%20' + query; }
 }
 </script>
 </div>
</div>

 </td>
 
 
 
 <td align="right" valign="top" class="bevel-right"></td>
 </tr>
</table>


<script type="text/javascript">
 var cancelBubble = false;
 function _go(url) { document.location = url; }
</script>
<div id="maincol"
 
>

 




<div class="expand">
<div id="colcontrol">
<style type="text/css">
 #file_flipper { white-space: nowrap; padding-right: 2em; }
 #file_flipper.hidden { display: none; }
 #file_flipper .pagelink { color: #0000CC; text-decoration: underline; }
 #file_flipper #visiblefiles { padding-left: 0.5em; padding-right: 0.5em; }
</style>
<table id="nav_and_rev" class="list"
 cellpadding="0" cellspacing="0" width="100%">
 <tr>
 
 <td nowrap="nowrap" class="src_crumbs src_nav" width="33%">
 <strong class="src_nav">Source path:&nbsp;</strong>
 <span id="crumb_root">
 
 <a href="/p/gamekit/source/browse/?r=887">svn</a>/&nbsp;</span>
 <span id="crumb_links" class="ifClosed"><a href="/p/gamekit/source/browse/trunk/?r=887">trunk</a><span class="sp">/&nbsp;</span><a href="/p/gamekit/source/browse/trunk/Dependencies/?r=887">Dependencies</a><span class="sp">/&nbsp;</span><a href="/p/gamekit/source/browse/trunk/Dependencies/Win32/?r=887">Win32</a><span class="sp">/&nbsp;</span><a href="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/?r=887">gles2</a><span class="sp">/&nbsp;</span><a href="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/?r=887">include</a><span class="sp">/&nbsp;</span><a href="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/GLSLANG/?r=887">GLSLANG</a><span class="sp">/&nbsp;</span>ShaderLang.h</span>
 
 


 </td>
 
 
 <td nowrap="nowrap" width="33%" align="right">
 <table cellpadding="0" cellspacing="0" style="font-size: 100%"><tr>
 
 
 <td class="flipper"><b>r887</b></td>
 
 <td class="flipper">
 <ul class="rightside">
 
 <li><a href="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/GLSLANG/ShaderLang.h?r=1299" title="Next">r1299&rsaquo;</a></li>
 
 </ul>
 </td>
 
 </tr></table>
 </td> 
 </tr>
</table>

<div class="fc">
 
 
 
<style type="text/css">
.undermouse span {
 background-image: url(http://www.gstatic.com/codesite/ph/images/comments.gif); }
</style>
<table class="opened" id="review_comment_area"
><tr>
<td id="nums">
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
<pre><table width="100%" id="nums_table_0"><tr id="gr_svn887_1"

><td id="1"><a href="#1">1</a></td></tr
><tr id="gr_svn887_2"

><td id="2"><a href="#2">2</a></td></tr
><tr id="gr_svn887_3"

><td id="3"><a href="#3">3</a></td></tr
><tr id="gr_svn887_4"

><td id="4"><a href="#4">4</a></td></tr
><tr id="gr_svn887_5"

><td id="5"><a href="#5">5</a></td></tr
><tr id="gr_svn887_6"

><td id="6"><a href="#6">6</a></td></tr
><tr id="gr_svn887_7"

><td id="7"><a href="#7">7</a></td></tr
><tr id="gr_svn887_8"

><td id="8"><a href="#8">8</a></td></tr
><tr id="gr_svn887_9"

><td id="9"><a href="#9">9</a></td></tr
><tr id="gr_svn887_10"

><td id="10"><a href="#10">10</a></td></tr
><tr id="gr_svn887_11"

><td id="11"><a href="#11">11</a></td></tr
><tr id="gr_svn887_12"

><td id="12"><a href="#12">12</a></td></tr
><tr id="gr_svn887_13"

><td id="13"><a href="#13">13</a></td></tr
><tr id="gr_svn887_14"

><td id="14"><a href="#14">14</a></td></tr
><tr id="gr_svn887_15"

><td id="15"><a href="#15">15</a></td></tr
><tr id="gr_svn887_16"

><td id="16"><a href="#16">16</a></td></tr
><tr id="gr_svn887_17"

><td id="17"><a href="#17">17</a></td></tr
><tr id="gr_svn887_18"

><td id="18"><a href="#18">18</a></td></tr
><tr id="gr_svn887_19"

><td id="19"><a href="#19">19</a></td></tr
><tr id="gr_svn887_20"

><td id="20"><a href="#20">20</a></td></tr
><tr id="gr_svn887_21"

><td id="21"><a href="#21">21</a></td></tr
><tr id="gr_svn887_22"

><td id="22"><a href="#22">22</a></td></tr
><tr id="gr_svn887_23"

><td id="23"><a href="#23">23</a></td></tr
><tr id="gr_svn887_24"

><td id="24"><a href="#24">24</a></td></tr
><tr id="gr_svn887_25"

><td id="25"><a href="#25">25</a></td></tr
><tr id="gr_svn887_26"

><td id="26"><a href="#26">26</a></td></tr
><tr id="gr_svn887_27"

><td id="27"><a href="#27">27</a></td></tr
><tr id="gr_svn887_28"

><td id="28"><a href="#28">28</a></td></tr
><tr id="gr_svn887_29"

><td id="29"><a href="#29">29</a></td></tr
><tr id="gr_svn887_30"

><td id="30"><a href="#30">30</a></td></tr
><tr id="gr_svn887_31"

><td id="31"><a href="#31">31</a></td></tr
><tr id="gr_svn887_32"

><td id="32"><a href="#32">32</a></td></tr
><tr id="gr_svn887_33"

><td id="33"><a href="#33">33</a></td></tr
><tr id="gr_svn887_34"

><td id="34"><a href="#34">34</a></td></tr
><tr id="gr_svn887_35"

><td id="35"><a href="#35">35</a></td></tr
><tr id="gr_svn887_36"

><td id="36"><a href="#36">36</a></td></tr
><tr id="gr_svn887_37"

><td id="37"><a href="#37">37</a></td></tr
><tr id="gr_svn887_38"

><td id="38"><a href="#38">38</a></td></tr
><tr id="gr_svn887_39"

><td id="39"><a href="#39">39</a></td></tr
><tr id="gr_svn887_40"

><td id="40"><a href="#40">40</a></td></tr
><tr id="gr_svn887_41"

><td id="41"><a href="#41">41</a></td></tr
><tr id="gr_svn887_42"

><td id="42"><a href="#42">42</a></td></tr
><tr id="gr_svn887_43"

><td id="43"><a href="#43">43</a></td></tr
><tr id="gr_svn887_44"

><td id="44"><a href="#44">44</a></td></tr
><tr id="gr_svn887_45"

><td id="45"><a href="#45">45</a></td></tr
><tr id="gr_svn887_46"

><td id="46"><a href="#46">46</a></td></tr
><tr id="gr_svn887_47"

><td id="47"><a href="#47">47</a></td></tr
><tr id="gr_svn887_48"

><td id="48"><a href="#48">48</a></td></tr
><tr id="gr_svn887_49"

><td id="49"><a href="#49">49</a></td></tr
><tr id="gr_svn887_50"

><td id="50"><a href="#50">50</a></td></tr
><tr id="gr_svn887_51"

><td id="51"><a href="#51">51</a></td></tr
><tr id="gr_svn887_52"

><td id="52"><a href="#52">52</a></td></tr
><tr id="gr_svn887_53"

><td id="53"><a href="#53">53</a></td></tr
><tr id="gr_svn887_54"

><td id="54"><a href="#54">54</a></td></tr
><tr id="gr_svn887_55"

><td id="55"><a href="#55">55</a></td></tr
><tr id="gr_svn887_56"

><td id="56"><a href="#56">56</a></td></tr
><tr id="gr_svn887_57"

><td id="57"><a href="#57">57</a></td></tr
><tr id="gr_svn887_58"

><td id="58"><a href="#58">58</a></td></tr
><tr id="gr_svn887_59"

><td id="59"><a href="#59">59</a></td></tr
><tr id="gr_svn887_60"

><td id="60"><a href="#60">60</a></td></tr
><tr id="gr_svn887_61"

><td id="61"><a href="#61">61</a></td></tr
><tr id="gr_svn887_62"

><td id="62"><a href="#62">62</a></td></tr
><tr id="gr_svn887_63"

><td id="63"><a href="#63">63</a></td></tr
><tr id="gr_svn887_64"

><td id="64"><a href="#64">64</a></td></tr
><tr id="gr_svn887_65"

><td id="65"><a href="#65">65</a></td></tr
><tr id="gr_svn887_66"

><td id="66"><a href="#66">66</a></td></tr
><tr id="gr_svn887_67"

><td id="67"><a href="#67">67</a></td></tr
><tr id="gr_svn887_68"

><td id="68"><a href="#68">68</a></td></tr
><tr id="gr_svn887_69"

><td id="69"><a href="#69">69</a></td></tr
><tr id="gr_svn887_70"

><td id="70"><a href="#70">70</a></td></tr
><tr id="gr_svn887_71"

><td id="71"><a href="#71">71</a></td></tr
><tr id="gr_svn887_72"

><td id="72"><a href="#72">72</a></td></tr
><tr id="gr_svn887_73"

><td id="73"><a href="#73">73</a></td></tr
><tr id="gr_svn887_74"

><td id="74"><a href="#74">74</a></td></tr
><tr id="gr_svn887_75"

><td id="75"><a href="#75">75</a></td></tr
><tr id="gr_svn887_76"

><td id="76"><a href="#76">76</a></td></tr
><tr id="gr_svn887_77"

><td id="77"><a href="#77">77</a></td></tr
><tr id="gr_svn887_78"

><td id="78"><a href="#78">78</a></td></tr
><tr id="gr_svn887_79"

><td id="79"><a href="#79">79</a></td></tr
><tr id="gr_svn887_80"

><td id="80"><a href="#80">80</a></td></tr
><tr id="gr_svn887_81"

><td id="81"><a href="#81">81</a></td></tr
><tr id="gr_svn887_82"

><td id="82"><a href="#82">82</a></td></tr
><tr id="gr_svn887_83"

><td id="83"><a href="#83">83</a></td></tr
><tr id="gr_svn887_84"

><td id="84"><a href="#84">84</a></td></tr
><tr id="gr_svn887_85"

><td id="85"><a href="#85">85</a></td></tr
><tr id="gr_svn887_86"

><td id="86"><a href="#86">86</a></td></tr
><tr id="gr_svn887_87"

><td id="87"><a href="#87">87</a></td></tr
><tr id="gr_svn887_88"

><td id="88"><a href="#88">88</a></td></tr
><tr id="gr_svn887_89"

><td id="89"><a href="#89">89</a></td></tr
><tr id="gr_svn887_90"

><td id="90"><a href="#90">90</a></td></tr
><tr id="gr_svn887_91"

><td id="91"><a href="#91">91</a></td></tr
><tr id="gr_svn887_92"

><td id="92"><a href="#92">92</a></td></tr
><tr id="gr_svn887_93"

><td id="93"><a href="#93">93</a></td></tr
><tr id="gr_svn887_94"

><td id="94"><a href="#94">94</a></td></tr
><tr id="gr_svn887_95"

><td id="95"><a href="#95">95</a></td></tr
><tr id="gr_svn887_96"

><td id="96"><a href="#96">96</a></td></tr
><tr id="gr_svn887_97"

><td id="97"><a href="#97">97</a></td></tr
><tr id="gr_svn887_98"

><td id="98"><a href="#98">98</a></td></tr
><tr id="gr_svn887_99"

><td id="99"><a href="#99">99</a></td></tr
><tr id="gr_svn887_100"

><td id="100"><a href="#100">100</a></td></tr
><tr id="gr_svn887_101"

><td id="101"><a href="#101">101</a></td></tr
><tr id="gr_svn887_102"

><td id="102"><a href="#102">102</a></td></tr
><tr id="gr_svn887_103"

><td id="103"><a href="#103">103</a></td></tr
><tr id="gr_svn887_104"

><td id="104"><a href="#104">104</a></td></tr
><tr id="gr_svn887_105"

><td id="105"><a href="#105">105</a></td></tr
><tr id="gr_svn887_106"

><td id="106"><a href="#106">106</a></td></tr
><tr id="gr_svn887_107"

><td id="107"><a href="#107">107</a></td></tr
><tr id="gr_svn887_108"

><td id="108"><a href="#108">108</a></td></tr
><tr id="gr_svn887_109"

><td id="109"><a href="#109">109</a></td></tr
><tr id="gr_svn887_110"

><td id="110"><a href="#110">110</a></td></tr
><tr id="gr_svn887_111"

><td id="111"><a href="#111">111</a></td></tr
><tr id="gr_svn887_112"

><td id="112"><a href="#112">112</a></td></tr
><tr id="gr_svn887_113"

><td id="113"><a href="#113">113</a></td></tr
><tr id="gr_svn887_114"

><td id="114"><a href="#114">114</a></td></tr
><tr id="gr_svn887_115"

><td id="115"><a href="#115">115</a></td></tr
><tr id="gr_svn887_116"

><td id="116"><a href="#116">116</a></td></tr
><tr id="gr_svn887_117"

><td id="117"><a href="#117">117</a></td></tr
><tr id="gr_svn887_118"

><td id="118"><a href="#118">118</a></td></tr
><tr id="gr_svn887_119"

><td id="119"><a href="#119">119</a></td></tr
><tr id="gr_svn887_120"

><td id="120"><a href="#120">120</a></td></tr
><tr id="gr_svn887_121"

><td id="121"><a href="#121">121</a></td></tr
><tr id="gr_svn887_122"

><td id="122"><a href="#122">122</a></td></tr
><tr id="gr_svn887_123"

><td id="123"><a href="#123">123</a></td></tr
><tr id="gr_svn887_124"

><td id="124"><a href="#124">124</a></td></tr
><tr id="gr_svn887_125"

><td id="125"><a href="#125">125</a></td></tr
><tr id="gr_svn887_126"

><td id="126"><a href="#126">126</a></td></tr
><tr id="gr_svn887_127"

><td id="127"><a href="#127">127</a></td></tr
><tr id="gr_svn887_128"

><td id="128"><a href="#128">128</a></td></tr
><tr id="gr_svn887_129"

><td id="129"><a href="#129">129</a></td></tr
><tr id="gr_svn887_130"

><td id="130"><a href="#130">130</a></td></tr
><tr id="gr_svn887_131"

><td id="131"><a href="#131">131</a></td></tr
><tr id="gr_svn887_132"

><td id="132"><a href="#132">132</a></td></tr
><tr id="gr_svn887_133"

><td id="133"><a href="#133">133</a></td></tr
><tr id="gr_svn887_134"

><td id="134"><a href="#134">134</a></td></tr
><tr id="gr_svn887_135"

><td id="135"><a href="#135">135</a></td></tr
><tr id="gr_svn887_136"

><td id="136"><a href="#136">136</a></td></tr
><tr id="gr_svn887_137"

><td id="137"><a href="#137">137</a></td></tr
><tr id="gr_svn887_138"

><td id="138"><a href="#138">138</a></td></tr
><tr id="gr_svn887_139"

><td id="139"><a href="#139">139</a></td></tr
><tr id="gr_svn887_140"

><td id="140"><a href="#140">140</a></td></tr
><tr id="gr_svn887_141"

><td id="141"><a href="#141">141</a></td></tr
><tr id="gr_svn887_142"

><td id="142"><a href="#142">142</a></td></tr
><tr id="gr_svn887_143"

><td id="143"><a href="#143">143</a></td></tr
><tr id="gr_svn887_144"

><td id="144"><a href="#144">144</a></td></tr
><tr id="gr_svn887_145"

><td id="145"><a href="#145">145</a></td></tr
><tr id="gr_svn887_146"

><td id="146"><a href="#146">146</a></td></tr
><tr id="gr_svn887_147"

><td id="147"><a href="#147">147</a></td></tr
><tr id="gr_svn887_148"

><td id="148"><a href="#148">148</a></td></tr
><tr id="gr_svn887_149"

><td id="149"><a href="#149">149</a></td></tr
><tr id="gr_svn887_150"

><td id="150"><a href="#150">150</a></td></tr
><tr id="gr_svn887_151"

><td id="151"><a href="#151">151</a></td></tr
><tr id="gr_svn887_152"

><td id="152"><a href="#152">152</a></td></tr
><tr id="gr_svn887_153"

><td id="153"><a href="#153">153</a></td></tr
><tr id="gr_svn887_154"

><td id="154"><a href="#154">154</a></td></tr
><tr id="gr_svn887_155"

><td id="155"><a href="#155">155</a></td></tr
><tr id="gr_svn887_156"

><td id="156"><a href="#156">156</a></td></tr
><tr id="gr_svn887_157"

><td id="157"><a href="#157">157</a></td></tr
><tr id="gr_svn887_158"

><td id="158"><a href="#158">158</a></td></tr
><tr id="gr_svn887_159"

><td id="159"><a href="#159">159</a></td></tr
><tr id="gr_svn887_160"

><td id="160"><a href="#160">160</a></td></tr
><tr id="gr_svn887_161"

><td id="161"><a href="#161">161</a></td></tr
><tr id="gr_svn887_162"

><td id="162"><a href="#162">162</a></td></tr
><tr id="gr_svn887_163"

><td id="163"><a href="#163">163</a></td></tr
><tr id="gr_svn887_164"

><td id="164"><a href="#164">164</a></td></tr
><tr id="gr_svn887_165"

><td id="165"><a href="#165">165</a></td></tr
><tr id="gr_svn887_166"

><td id="166"><a href="#166">166</a></td></tr
><tr id="gr_svn887_167"

><td id="167"><a href="#167">167</a></td></tr
><tr id="gr_svn887_168"

><td id="168"><a href="#168">168</a></td></tr
><tr id="gr_svn887_169"

><td id="169"><a href="#169">169</a></td></tr
><tr id="gr_svn887_170"

><td id="170"><a href="#170">170</a></td></tr
><tr id="gr_svn887_171"

><td id="171"><a href="#171">171</a></td></tr
><tr id="gr_svn887_172"

><td id="172"><a href="#172">172</a></td></tr
><tr id="gr_svn887_173"

><td id="173"><a href="#173">173</a></td></tr
><tr id="gr_svn887_174"

><td id="174"><a href="#174">174</a></td></tr
><tr id="gr_svn887_175"

><td id="175"><a href="#175">175</a></td></tr
><tr id="gr_svn887_176"

><td id="176"><a href="#176">176</a></td></tr
><tr id="gr_svn887_177"

><td id="177"><a href="#177">177</a></td></tr
><tr id="gr_svn887_178"

><td id="178"><a href="#178">178</a></td></tr
><tr id="gr_svn887_179"

><td id="179"><a href="#179">179</a></td></tr
><tr id="gr_svn887_180"

><td id="180"><a href="#180">180</a></td></tr
><tr id="gr_svn887_181"

><td id="181"><a href="#181">181</a></td></tr
><tr id="gr_svn887_182"

><td id="182"><a href="#182">182</a></td></tr
><tr id="gr_svn887_183"

><td id="183"><a href="#183">183</a></td></tr
><tr id="gr_svn887_184"

><td id="184"><a href="#184">184</a></td></tr
><tr id="gr_svn887_185"

><td id="185"><a href="#185">185</a></td></tr
><tr id="gr_svn887_186"

><td id="186"><a href="#186">186</a></td></tr
><tr id="gr_svn887_187"

><td id="187"><a href="#187">187</a></td></tr
><tr id="gr_svn887_188"

><td id="188"><a href="#188">188</a></td></tr
><tr id="gr_svn887_189"

><td id="189"><a href="#189">189</a></td></tr
><tr id="gr_svn887_190"

><td id="190"><a href="#190">190</a></td></tr
><tr id="gr_svn887_191"

><td id="191"><a href="#191">191</a></td></tr
><tr id="gr_svn887_192"

><td id="192"><a href="#192">192</a></td></tr
><tr id="gr_svn887_193"

><td id="193"><a href="#193">193</a></td></tr
><tr id="gr_svn887_194"

><td id="194"><a href="#194">194</a></td></tr
><tr id="gr_svn887_195"

><td id="195"><a href="#195">195</a></td></tr
><tr id="gr_svn887_196"

><td id="196"><a href="#196">196</a></td></tr
><tr id="gr_svn887_197"

><td id="197"><a href="#197">197</a></td></tr
><tr id="gr_svn887_198"

><td id="198"><a href="#198">198</a></td></tr
><tr id="gr_svn887_199"

><td id="199"><a href="#199">199</a></td></tr
><tr id="gr_svn887_200"

><td id="200"><a href="#200">200</a></td></tr
><tr id="gr_svn887_201"

><td id="201"><a href="#201">201</a></td></tr
><tr id="gr_svn887_202"

><td id="202"><a href="#202">202</a></td></tr
><tr id="gr_svn887_203"

><td id="203"><a href="#203">203</a></td></tr
><tr id="gr_svn887_204"

><td id="204"><a href="#204">204</a></td></tr
><tr id="gr_svn887_205"

><td id="205"><a href="#205">205</a></td></tr
><tr id="gr_svn887_206"

><td id="206"><a href="#206">206</a></td></tr
><tr id="gr_svn887_207"

><td id="207"><a href="#207">207</a></td></tr
><tr id="gr_svn887_208"

><td id="208"><a href="#208">208</a></td></tr
><tr id="gr_svn887_209"

><td id="209"><a href="#209">209</a></td></tr
><tr id="gr_svn887_210"

><td id="210"><a href="#210">210</a></td></tr
><tr id="gr_svn887_211"

><td id="211"><a href="#211">211</a></td></tr
><tr id="gr_svn887_212"

><td id="212"><a href="#212">212</a></td></tr
><tr id="gr_svn887_213"

><td id="213"><a href="#213">213</a></td></tr
><tr id="gr_svn887_214"

><td id="214"><a href="#214">214</a></td></tr
><tr id="gr_svn887_215"

><td id="215"><a href="#215">215</a></td></tr
><tr id="gr_svn887_216"

><td id="216"><a href="#216">216</a></td></tr
><tr id="gr_svn887_217"

><td id="217"><a href="#217">217</a></td></tr
><tr id="gr_svn887_218"

><td id="218"><a href="#218">218</a></td></tr
><tr id="gr_svn887_219"

><td id="219"><a href="#219">219</a></td></tr
><tr id="gr_svn887_220"

><td id="220"><a href="#220">220</a></td></tr
><tr id="gr_svn887_221"

><td id="221"><a href="#221">221</a></td></tr
><tr id="gr_svn887_222"

><td id="222"><a href="#222">222</a></td></tr
><tr id="gr_svn887_223"

><td id="223"><a href="#223">223</a></td></tr
><tr id="gr_svn887_224"

><td id="224"><a href="#224">224</a></td></tr
><tr id="gr_svn887_225"

><td id="225"><a href="#225">225</a></td></tr
><tr id="gr_svn887_226"

><td id="226"><a href="#226">226</a></td></tr
><tr id="gr_svn887_227"

><td id="227"><a href="#227">227</a></td></tr
><tr id="gr_svn887_228"

><td id="228"><a href="#228">228</a></td></tr
><tr id="gr_svn887_229"

><td id="229"><a href="#229">229</a></td></tr
><tr id="gr_svn887_230"

><td id="230"><a href="#230">230</a></td></tr
><tr id="gr_svn887_231"

><td id="231"><a href="#231">231</a></td></tr
><tr id="gr_svn887_232"

><td id="232"><a href="#232">232</a></td></tr
><tr id="gr_svn887_233"

><td id="233"><a href="#233">233</a></td></tr
><tr id="gr_svn887_234"

><td id="234"><a href="#234">234</a></td></tr
><tr id="gr_svn887_235"

><td id="235"><a href="#235">235</a></td></tr
><tr id="gr_svn887_236"

><td id="236"><a href="#236">236</a></td></tr
><tr id="gr_svn887_237"

><td id="237"><a href="#237">237</a></td></tr
><tr id="gr_svn887_238"

><td id="238"><a href="#238">238</a></td></tr
><tr id="gr_svn887_239"

><td id="239"><a href="#239">239</a></td></tr
><tr id="gr_svn887_240"

><td id="240"><a href="#240">240</a></td></tr
><tr id="gr_svn887_241"

><td id="241"><a href="#241">241</a></td></tr
><tr id="gr_svn887_242"

><td id="242"><a href="#242">242</a></td></tr
><tr id="gr_svn887_243"

><td id="243"><a href="#243">243</a></td></tr
><tr id="gr_svn887_244"

><td id="244"><a href="#244">244</a></td></tr
><tr id="gr_svn887_245"

><td id="245"><a href="#245">245</a></td></tr
><tr id="gr_svn887_246"

><td id="246"><a href="#246">246</a></td></tr
><tr id="gr_svn887_247"

><td id="247"><a href="#247">247</a></td></tr
><tr id="gr_svn887_248"

><td id="248"><a href="#248">248</a></td></tr
><tr id="gr_svn887_249"

><td id="249"><a href="#249">249</a></td></tr
><tr id="gr_svn887_250"

><td id="250"><a href="#250">250</a></td></tr
><tr id="gr_svn887_251"

><td id="251"><a href="#251">251</a></td></tr
><tr id="gr_svn887_252"

><td id="252"><a href="#252">252</a></td></tr
><tr id="gr_svn887_253"

><td id="253"><a href="#253">253</a></td></tr
><tr id="gr_svn887_254"

><td id="254"><a href="#254">254</a></td></tr
><tr id="gr_svn887_255"

><td id="255"><a href="#255">255</a></td></tr
><tr id="gr_svn887_256"

><td id="256"><a href="#256">256</a></td></tr
><tr id="gr_svn887_257"

><td id="257"><a href="#257">257</a></td></tr
><tr id="gr_svn887_258"

><td id="258"><a href="#258">258</a></td></tr
></table></pre>
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
</td>
<td id="lines">
<pre><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
<pre class="prettyprint "><table id="src_table_0"><tr
id=sl_svn887_1

><td class="source">//<br></td></tr
><tr
id=sl_svn887_2

><td class="source">// Copyright (c) 2002-2010 The ANGLE Project Authors. All rights reserved.<br></td></tr
><tr
id=sl_svn887_3

><td class="source">// Use of this source code is governed by a BSD-style license that can be<br></td></tr
><tr
id=sl_svn887_4

><td class="source">// found in the LICENSE file.<br></td></tr
><tr
id=sl_svn887_5

><td class="source">//<br></td></tr
><tr
id=sl_svn887_6

><td class="source">#ifndef _COMPILER_INTERFACE_INCLUDED_<br></td></tr
><tr
id=sl_svn887_7

><td class="source">#define _COMPILER_INTERFACE_INCLUDED_<br></td></tr
><tr
id=sl_svn887_8

><td class="source"><br></td></tr
><tr
id=sl_svn887_9

><td class="source">//<br></td></tr
><tr
id=sl_svn887_10

><td class="source">// This is the platform independent interface between an OGL driver<br></td></tr
><tr
id=sl_svn887_11

><td class="source">// and the shading language compiler.<br></td></tr
><tr
id=sl_svn887_12

><td class="source">//<br></td></tr
><tr
id=sl_svn887_13

><td class="source"><br></td></tr
><tr
id=sl_svn887_14

><td class="source">#ifdef __cplusplus<br></td></tr
><tr
id=sl_svn887_15

><td class="source">extern &quot;C&quot; {<br></td></tr
><tr
id=sl_svn887_16

><td class="source">#endif<br></td></tr
><tr
id=sl_svn887_17

><td class="source"><br></td></tr
><tr
id=sl_svn887_18

><td class="source">// Version number for shader translation API.<br></td></tr
><tr
id=sl_svn887_19

><td class="source">// It is incremented everytime the API changes.<br></td></tr
><tr
id=sl_svn887_20

><td class="source">#define SH_VERSION 103<br></td></tr
><tr
id=sl_svn887_21

><td class="source"><br></td></tr
><tr
id=sl_svn887_22

><td class="source">//<br></td></tr
><tr
id=sl_svn887_23

><td class="source">// The names of the following enums have been derived by replacing GL prefix<br></td></tr
><tr
id=sl_svn887_24

><td class="source">// with SH. For example, SH_INFO_LOG_LENGTH is equivalent to GL_INFO_LOG_LENGTH.<br></td></tr
><tr
id=sl_svn887_25

><td class="source">// The enum values are also equal to the values of their GL counterpart. This<br></td></tr
><tr
id=sl_svn887_26

><td class="source">// is done to make it easier for applications to use the shader library.<br></td></tr
><tr
id=sl_svn887_27

><td class="source">//<br></td></tr
><tr
id=sl_svn887_28

><td class="source">typedef enum {<br></td></tr
><tr
id=sl_svn887_29

><td class="source">  SH_FRAGMENT_SHADER = 0x8B30,<br></td></tr
><tr
id=sl_svn887_30

><td class="source">  SH_VERTEX_SHADER   = 0x8B31<br></td></tr
><tr
id=sl_svn887_31

><td class="source">} ShShaderType;<br></td></tr
><tr
id=sl_svn887_32

><td class="source"><br></td></tr
><tr
id=sl_svn887_33

><td class="source">typedef enum {<br></td></tr
><tr
id=sl_svn887_34

><td class="source">  SH_GLES2_SPEC = 0x8B40,<br></td></tr
><tr
id=sl_svn887_35

><td class="source">  SH_WEBGL_SPEC = 0x8B41<br></td></tr
><tr
id=sl_svn887_36

><td class="source">} ShShaderSpec;<br></td></tr
><tr
id=sl_svn887_37

><td class="source"><br></td></tr
><tr
id=sl_svn887_38

><td class="source">typedef enum {<br></td></tr
><tr
id=sl_svn887_39

><td class="source">  SH_NONE           = 0,<br></td></tr
><tr
id=sl_svn887_40

><td class="source">  SH_INT            = 0x1404,<br></td></tr
><tr
id=sl_svn887_41

><td class="source">  SH_FLOAT          = 0x1406,<br></td></tr
><tr
id=sl_svn887_42

><td class="source">  SH_FLOAT_VEC2     = 0x8B50,<br></td></tr
><tr
id=sl_svn887_43

><td class="source">  SH_FLOAT_VEC3     = 0x8B51,<br></td></tr
><tr
id=sl_svn887_44

><td class="source">  SH_FLOAT_VEC4     = 0x8B52,<br></td></tr
><tr
id=sl_svn887_45

><td class="source">  SH_INT_VEC2       = 0x8B53,<br></td></tr
><tr
id=sl_svn887_46

><td class="source">  SH_INT_VEC3       = 0x8B54,<br></td></tr
><tr
id=sl_svn887_47

><td class="source">  SH_INT_VEC4       = 0x8B55,<br></td></tr
><tr
id=sl_svn887_48

><td class="source">  SH_BOOL           = 0x8B56,<br></td></tr
><tr
id=sl_svn887_49

><td class="source">  SH_BOOL_VEC2      = 0x8B57,<br></td></tr
><tr
id=sl_svn887_50

><td class="source">  SH_BOOL_VEC3      = 0x8B58,<br></td></tr
><tr
id=sl_svn887_51

><td class="source">  SH_BOOL_VEC4      = 0x8B59,<br></td></tr
><tr
id=sl_svn887_52

><td class="source">  SH_FLOAT_MAT2     = 0x8B5A,<br></td></tr
><tr
id=sl_svn887_53

><td class="source">  SH_FLOAT_MAT3     = 0x8B5B,<br></td></tr
><tr
id=sl_svn887_54

><td class="source">  SH_FLOAT_MAT4     = 0x8B5C,<br></td></tr
><tr
id=sl_svn887_55

><td class="source">  SH_SAMPLER_2D     = 0x8B5E,<br></td></tr
><tr
id=sl_svn887_56

><td class="source">  SH_SAMPLER_CUBE   = 0x8B60<br></td></tr
><tr
id=sl_svn887_57

><td class="source">} ShDataType;<br></td></tr
><tr
id=sl_svn887_58

><td class="source"><br></td></tr
><tr
id=sl_svn887_59

><td class="source">typedef enum {<br></td></tr
><tr
id=sl_svn887_60

><td class="source">  SH_INFO_LOG_LENGTH             =  0x8B84,<br></td></tr
><tr
id=sl_svn887_61

><td class="source">  SH_OBJECT_CODE_LENGTH          =  0x8B88,  // GL_SHADER_SOURCE_LENGTH<br></td></tr
><tr
id=sl_svn887_62

><td class="source">  SH_ACTIVE_UNIFORMS             =  0x8B86,<br></td></tr
><tr
id=sl_svn887_63

><td class="source">  SH_ACTIVE_UNIFORM_MAX_LENGTH   =  0x8B87,<br></td></tr
><tr
id=sl_svn887_64

><td class="source">  SH_ACTIVE_ATTRIBUTES           =  0x8B89,<br></td></tr
><tr
id=sl_svn887_65

><td class="source">  SH_ACTIVE_ATTRIBUTE_MAX_LENGTH =  0x8B8A<br></td></tr
><tr
id=sl_svn887_66

><td class="source">} ShShaderInfo;<br></td></tr
><tr
id=sl_svn887_67

><td class="source"><br></td></tr
><tr
id=sl_svn887_68

><td class="source">// Compile options.<br></td></tr
><tr
id=sl_svn887_69

><td class="source">typedef enum {<br></td></tr
><tr
id=sl_svn887_70

><td class="source">  SH_VALIDATE               = 0,<br></td></tr
><tr
id=sl_svn887_71

><td class="source">  SH_VALIDATE_LOOP_INDEXING = 0x0001,<br></td></tr
><tr
id=sl_svn887_72

><td class="source">  SH_INTERMEDIATE_TREE      = 0x0002,<br></td></tr
><tr
id=sl_svn887_73

><td class="source">  SH_OBJECT_CODE            = 0x0004,<br></td></tr
><tr
id=sl_svn887_74

><td class="source">  SH_ATTRIBUTES_UNIFORMS    = 0x0008,<br></td></tr
><tr
id=sl_svn887_75

><td class="source">  SH_LINE_DIRECTIVES        = 0x0010,<br></td></tr
><tr
id=sl_svn887_76

><td class="source">  SH_SOURCE_PATH            = 0x0200<br></td></tr
><tr
id=sl_svn887_77

><td class="source">} ShCompileOptions;<br></td></tr
><tr
id=sl_svn887_78

><td class="source"><br></td></tr
><tr
id=sl_svn887_79

><td class="source">//<br></td></tr
><tr
id=sl_svn887_80

><td class="source">// Driver must call this first, once, before doing any other<br></td></tr
><tr
id=sl_svn887_81

><td class="source">// compiler operations.<br></td></tr
><tr
id=sl_svn887_82

><td class="source">// If the function succeeds, the return value is nonzero, else zero.<br></td></tr
><tr
id=sl_svn887_83

><td class="source">//<br></td></tr
><tr
id=sl_svn887_84

><td class="source">int ShInitialize();<br></td></tr
><tr
id=sl_svn887_85

><td class="source">//<br></td></tr
><tr
id=sl_svn887_86

><td class="source">// Driver should call this at shutdown.<br></td></tr
><tr
id=sl_svn887_87

><td class="source">// If the function succeeds, the return value is nonzero, else zero.<br></td></tr
><tr
id=sl_svn887_88

><td class="source">//<br></td></tr
><tr
id=sl_svn887_89

><td class="source">int ShFinalize();<br></td></tr
><tr
id=sl_svn887_90

><td class="source"><br></td></tr
><tr
id=sl_svn887_91

><td class="source">//<br></td></tr
><tr
id=sl_svn887_92

><td class="source">// Implementation dependent built-in resources (constants and extensions).<br></td></tr
><tr
id=sl_svn887_93

><td class="source">// The names for these resources has been obtained by stripping gl_/GL_.<br></td></tr
><tr
id=sl_svn887_94

><td class="source">//<br></td></tr
><tr
id=sl_svn887_95

><td class="source">typedef struct<br></td></tr
><tr
id=sl_svn887_96

><td class="source">{<br></td></tr
><tr
id=sl_svn887_97

><td class="source">    // Constants.<br></td></tr
><tr
id=sl_svn887_98

><td class="source">    int MaxVertexAttribs;<br></td></tr
><tr
id=sl_svn887_99

><td class="source">    int MaxVertexUniformVectors;<br></td></tr
><tr
id=sl_svn887_100

><td class="source">    int MaxVaryingVectors;<br></td></tr
><tr
id=sl_svn887_101

><td class="source">    int MaxVertexTextureImageUnits;<br></td></tr
><tr
id=sl_svn887_102

><td class="source">    int MaxCombinedTextureImageUnits;<br></td></tr
><tr
id=sl_svn887_103

><td class="source">    int MaxTextureImageUnits;<br></td></tr
><tr
id=sl_svn887_104

><td class="source">    int MaxFragmentUniformVectors;<br></td></tr
><tr
id=sl_svn887_105

><td class="source">    int MaxDrawBuffers;<br></td></tr
><tr
id=sl_svn887_106

><td class="source"><br></td></tr
><tr
id=sl_svn887_107

><td class="source">    // Extensions.<br></td></tr
><tr
id=sl_svn887_108

><td class="source">    // Set to 1 to enable the extension, else 0.<br></td></tr
><tr
id=sl_svn887_109

><td class="source">    int OES_standard_derivatives;<br></td></tr
><tr
id=sl_svn887_110

><td class="source">} ShBuiltInResources;<br></td></tr
><tr
id=sl_svn887_111

><td class="source"><br></td></tr
><tr
id=sl_svn887_112

><td class="source">//<br></td></tr
><tr
id=sl_svn887_113

><td class="source">// Initialize built-in resources with minimum expected values.<br></td></tr
><tr
id=sl_svn887_114

><td class="source">//<br></td></tr
><tr
id=sl_svn887_115

><td class="source">void ShInitBuiltInResources(ShBuiltInResources* resources);<br></td></tr
><tr
id=sl_svn887_116

><td class="source"><br></td></tr
><tr
id=sl_svn887_117

><td class="source">//<br></td></tr
><tr
id=sl_svn887_118

><td class="source">// ShHandle held by but opaque to the driver.  It is allocated,<br></td></tr
><tr
id=sl_svn887_119

><td class="source">// managed, and de-allocated by the compiler. It&#39;s contents <br></td></tr
><tr
id=sl_svn887_120

><td class="source">// are defined by and used by the compiler.<br></td></tr
><tr
id=sl_svn887_121

><td class="source">//<br></td></tr
><tr
id=sl_svn887_122

><td class="source">// If handle creation fails, 0 will be returned.<br></td></tr
><tr
id=sl_svn887_123

><td class="source">//<br></td></tr
><tr
id=sl_svn887_124

><td class="source">typedef void* ShHandle;<br></td></tr
><tr
id=sl_svn887_125

><td class="source"><br></td></tr
><tr
id=sl_svn887_126

><td class="source">//<br></td></tr
><tr
id=sl_svn887_127

><td class="source">// Driver calls these to create and destroy compiler objects.<br></td></tr
><tr
id=sl_svn887_128

><td class="source">//<br></td></tr
><tr
id=sl_svn887_129

><td class="source">// Returns the handle of constructed compiler.<br></td></tr
><tr
id=sl_svn887_130

><td class="source">// Parameters:<br></td></tr
><tr
id=sl_svn887_131

><td class="source">// type: Specifies the type of shader - SH_FRAGMENT_SHADER or SH_VERTEX_SHADER.<br></td></tr
><tr
id=sl_svn887_132

><td class="source">// spec: Specifies the language spec the compiler must conform to -<br></td></tr
><tr
id=sl_svn887_133

><td class="source">//       SH_GLES2_SPEC or SH_WEBGL_SPEC.<br></td></tr
><tr
id=sl_svn887_134

><td class="source">// resources: Specifies the built-in resources.<br></td></tr
><tr
id=sl_svn887_135

><td class="source">ShHandle ShConstructCompiler(ShShaderType type, ShShaderSpec spec,<br></td></tr
><tr
id=sl_svn887_136

><td class="source">                             const ShBuiltInResources* resources);<br></td></tr
><tr
id=sl_svn887_137

><td class="source">void ShDestruct(ShHandle handle);<br></td></tr
><tr
id=sl_svn887_138

><td class="source"><br></td></tr
><tr
id=sl_svn887_139

><td class="source">//<br></td></tr
><tr
id=sl_svn887_140

><td class="source">// Compiles the given shader source.<br></td></tr
><tr
id=sl_svn887_141

><td class="source">// If the function succeeds, the return value is nonzero, else zero.<br></td></tr
><tr
id=sl_svn887_142

><td class="source">// Parameters:<br></td></tr
><tr
id=sl_svn887_143

><td class="source">// handle: Specifies the handle of compiler to be used.<br></td></tr
><tr
id=sl_svn887_144

><td class="source">// shaderStrings: Specifies an array of pointers to null-terminated strings<br></td></tr
><tr
id=sl_svn887_145

><td class="source">//                containing the shader source code.<br></td></tr
><tr
id=sl_svn887_146

><td class="source">// numStrings: Specifies the number of elements in shaderStrings array.<br></td></tr
><tr
id=sl_svn887_147

><td class="source">// compileOptions: A mask containing the following parameters:<br></td></tr
><tr
id=sl_svn887_148

><td class="source">// SH_VALIDATE: Validates shader to ensure that it conforms to the spec<br></td></tr
><tr
id=sl_svn887_149

><td class="source">//              specified during compiler construction.<br></td></tr
><tr
id=sl_svn887_150

><td class="source">// SH_VALIDATE_LOOP_INDEXING: Validates loop and indexing in the shader to<br></td></tr
><tr
id=sl_svn887_151

><td class="source">//                            ensure that they do not exceed the minimum<br></td></tr
><tr
id=sl_svn887_152

><td class="source">//                            functionality mandated in GLSL 1.0 spec,<br></td></tr
><tr
id=sl_svn887_153

><td class="source">//                            Appendix A, Section 4 and 5.<br></td></tr
><tr
id=sl_svn887_154

><td class="source">//                            There is no need to specify this parameter when<br></td></tr
><tr
id=sl_svn887_155

><td class="source">//                            compiling for WebGL - it is implied.<br></td></tr
><tr
id=sl_svn887_156

><td class="source">// SH_INTERMEDIATE_TREE: Writes intermediate tree to info log.<br></td></tr
><tr
id=sl_svn887_157

><td class="source">//                       Can be queried by calling ShGetInfoLog().<br></td></tr
><tr
id=sl_svn887_158

><td class="source">// SH_OBJECT_CODE: Translates intermediate tree to glsl or hlsl shader.<br></td></tr
><tr
id=sl_svn887_159

><td class="source">//                 Can be queried by calling ShGetObjectCode().<br></td></tr
><tr
id=sl_svn887_160

><td class="source">// SH_ATTRIBUTES_UNIFORMS: Extracts attributes and uniforms.<br></td></tr
><tr
id=sl_svn887_161

><td class="source">//                         Can be queried by calling ShGetActiveAttrib() and<br></td></tr
><tr
id=sl_svn887_162

><td class="source">//                         ShGetActiveUniform().<br></td></tr
><tr
id=sl_svn887_163

><td class="source">//<br></td></tr
><tr
id=sl_svn887_164

><td class="source">int ShCompile(<br></td></tr
><tr
id=sl_svn887_165

><td class="source">    const ShHandle handle,<br></td></tr
><tr
id=sl_svn887_166

><td class="source">    const char* const shaderStrings[],<br></td></tr
><tr
id=sl_svn887_167

><td class="source">    const int numStrings,<br></td></tr
><tr
id=sl_svn887_168

><td class="source">    int compileOptions<br></td></tr
><tr
id=sl_svn887_169

><td class="source">    );<br></td></tr
><tr
id=sl_svn887_170

><td class="source"><br></td></tr
><tr
id=sl_svn887_171

><td class="source">// Returns a parameter from a compiled shader.<br></td></tr
><tr
id=sl_svn887_172

><td class="source">// Parameters:<br></td></tr
><tr
id=sl_svn887_173

><td class="source">// handle: Specifies the compiler<br></td></tr
><tr
id=sl_svn887_174

><td class="source">// pname: Specifies the parameter to query.<br></td></tr
><tr
id=sl_svn887_175

><td class="source">// The following parameters are defined:<br></td></tr
><tr
id=sl_svn887_176

><td class="source">// SH_INFO_LOG_LENGTH: the number of characters in the information log<br></td></tr
><tr
id=sl_svn887_177

><td class="source">//                     including the null termination character.<br></td></tr
><tr
id=sl_svn887_178

><td class="source">// SH_OBJECT_CODE_LENGTH: the number of characters in the object code<br></td></tr
><tr
id=sl_svn887_179

><td class="source">//                        including the null termination character.<br></td></tr
><tr
id=sl_svn887_180

><td class="source">// SH_ACTIVE_ATTRIBUTES: the number of active attribute variables.<br></td></tr
><tr
id=sl_svn887_181

><td class="source">// SH_ACTIVE_ATTRIBUTE_MAX_LENGTH: the length of the longest active attribute<br></td></tr
><tr
id=sl_svn887_182

><td class="source">//                                 variable name including the null<br></td></tr
><tr
id=sl_svn887_183

><td class="source">//                                 termination character.<br></td></tr
><tr
id=sl_svn887_184

><td class="source">// SH_ACTIVE_UNIFORMS: the number of active uniform variables.<br></td></tr
><tr
id=sl_svn887_185

><td class="source">// SH_ACTIVE_UNIFORM_MAX_LENGTH: the length of the longest active uniform<br></td></tr
><tr
id=sl_svn887_186

><td class="source">//                               variable name including the null<br></td></tr
><tr
id=sl_svn887_187

><td class="source">//                               termination character.<br></td></tr
><tr
id=sl_svn887_188

><td class="source">// <br></td></tr
><tr
id=sl_svn887_189

><td class="source">// params: Requested parameter<br></td></tr
><tr
id=sl_svn887_190

><td class="source">void ShGetInfo(const ShHandle handle, ShShaderInfo pname, int* params);<br></td></tr
><tr
id=sl_svn887_191

><td class="source"><br></td></tr
><tr
id=sl_svn887_192

><td class="source">// Returns nul-terminated information log for a compiled shader.<br></td></tr
><tr
id=sl_svn887_193

><td class="source">// Parameters:<br></td></tr
><tr
id=sl_svn887_194

><td class="source">// handle: Specifies the compiler<br></td></tr
><tr
id=sl_svn887_195

><td class="source">// infoLog: Specifies an array of characters that is used to return<br></td></tr
><tr
id=sl_svn887_196

><td class="source">//          the information log. It is assumed that infoLog has enough memory<br></td></tr
><tr
id=sl_svn887_197

><td class="source">//          to accomodate the information log. The size of the buffer required<br></td></tr
><tr
id=sl_svn887_198

><td class="source">//          to store the returned information log can be obtained by calling<br></td></tr
><tr
id=sl_svn887_199

><td class="source">//          ShGetInfo with SH_INFO_LOG_LENGTH.<br></td></tr
><tr
id=sl_svn887_200

><td class="source">void ShGetInfoLog(const ShHandle handle, char* infoLog);<br></td></tr
><tr
id=sl_svn887_201

><td class="source"><br></td></tr
><tr
id=sl_svn887_202

><td class="source">// Returns null-terminated object code for a compiled shader.<br></td></tr
><tr
id=sl_svn887_203

><td class="source">// Parameters:<br></td></tr
><tr
id=sl_svn887_204

><td class="source">// handle: Specifies the compiler<br></td></tr
><tr
id=sl_svn887_205

><td class="source">// infoLog: Specifies an array of characters that is used to return<br></td></tr
><tr
id=sl_svn887_206

><td class="source">//          the object code. It is assumed that infoLog has enough memory to<br></td></tr
><tr
id=sl_svn887_207

><td class="source">//          accomodate the object code. The size of the buffer required to<br></td></tr
><tr
id=sl_svn887_208

><td class="source">//          store the returned object code can be obtained by calling<br></td></tr
><tr
id=sl_svn887_209

><td class="source">//          ShGetInfo with SH_OBJECT_CODE_LENGTH.<br></td></tr
><tr
id=sl_svn887_210

><td class="source">void ShGetObjectCode(const ShHandle handle, char* objCode);<br></td></tr
><tr
id=sl_svn887_211

><td class="source"><br></td></tr
><tr
id=sl_svn887_212

><td class="source">// Returns information about an active attribute variable.<br></td></tr
><tr
id=sl_svn887_213

><td class="source">// Parameters:<br></td></tr
><tr
id=sl_svn887_214

><td class="source">// handle: Specifies the compiler<br></td></tr
><tr
id=sl_svn887_215

><td class="source">// index: Specifies the index of the attribute variable to be queried.<br></td></tr
><tr
id=sl_svn887_216

><td class="source">// length: Returns the number of characters actually written in the string<br></td></tr
><tr
id=sl_svn887_217

><td class="source">//         indicated by name (excluding the null terminator) if a value other<br></td></tr
><tr
id=sl_svn887_218

><td class="source">//         than NULL is passed.<br></td></tr
><tr
id=sl_svn887_219

><td class="source">// size: Returns the size of the attribute variable.<br></td></tr
><tr
id=sl_svn887_220

><td class="source">// type: Returns the data type of the attribute variable.<br></td></tr
><tr
id=sl_svn887_221

><td class="source">// name: Returns a null terminated string containing the name of the<br></td></tr
><tr
id=sl_svn887_222

><td class="source">//       attribute variable. It is assumed that name has enough memory to<br></td></tr
><tr
id=sl_svn887_223

><td class="source">//       accomodate the attribute variable name. The size of the buffer<br></td></tr
><tr
id=sl_svn887_224

><td class="source">//       required to store the attribute variable name can be obtained by<br></td></tr
><tr
id=sl_svn887_225

><td class="source">//       calling ShGetInfo with SH_ACTIVE_ATTRIBUTE_MAX_LENGTH.<br></td></tr
><tr
id=sl_svn887_226

><td class="source">void ShGetActiveAttrib(const ShHandle handle,<br></td></tr
><tr
id=sl_svn887_227

><td class="source">                       int index,<br></td></tr
><tr
id=sl_svn887_228

><td class="source">                       int* length,<br></td></tr
><tr
id=sl_svn887_229

><td class="source">                       int* size,<br></td></tr
><tr
id=sl_svn887_230

><td class="source">                       ShDataType* type,<br></td></tr
><tr
id=sl_svn887_231

><td class="source">                       char* name);<br></td></tr
><tr
id=sl_svn887_232

><td class="source"><br></td></tr
><tr
id=sl_svn887_233

><td class="source">// Returns information about an active uniform variable.<br></td></tr
><tr
id=sl_svn887_234

><td class="source">// Parameters:<br></td></tr
><tr
id=sl_svn887_235

><td class="source">// handle: Specifies the compiler<br></td></tr
><tr
id=sl_svn887_236

><td class="source">// index: Specifies the index of the uniform variable to be queried.<br></td></tr
><tr
id=sl_svn887_237

><td class="source">// length: Returns the number of characters actually written in the string<br></td></tr
><tr
id=sl_svn887_238

><td class="source">//         indicated by name (excluding the null terminator) if a value<br></td></tr
><tr
id=sl_svn887_239

><td class="source">//         other than NULL is passed.<br></td></tr
><tr
id=sl_svn887_240

><td class="source">// size: Returns the size of the uniform variable.<br></td></tr
><tr
id=sl_svn887_241

><td class="source">// type: Returns the data type of the uniform variable.<br></td></tr
><tr
id=sl_svn887_242

><td class="source">// name: Returns a null terminated string containing the name of the<br></td></tr
><tr
id=sl_svn887_243

><td class="source">//       uniform variable. It is assumed that name has enough memory to<br></td></tr
><tr
id=sl_svn887_244

><td class="source">//       accomodate the uniform variable name. The size of the buffer required<br></td></tr
><tr
id=sl_svn887_245

><td class="source">//       to store the uniform variable name can be obtained by calling<br></td></tr
><tr
id=sl_svn887_246

><td class="source">//       ShGetInfo with SH_ACTIVE_UNIFORMS_MAX_LENGTH.<br></td></tr
><tr
id=sl_svn887_247

><td class="source">void ShGetActiveUniform(const ShHandle handle,<br></td></tr
><tr
id=sl_svn887_248

><td class="source">                        int index,<br></td></tr
><tr
id=sl_svn887_249

><td class="source">                        int* length,<br></td></tr
><tr
id=sl_svn887_250

><td class="source">                        int* size,<br></td></tr
><tr
id=sl_svn887_251

><td class="source">                        ShDataType* type,<br></td></tr
><tr
id=sl_svn887_252

><td class="source">                        char* name);<br></td></tr
><tr
id=sl_svn887_253

><td class="source"><br></td></tr
><tr
id=sl_svn887_254

><td class="source">#ifdef __cplusplus<br></td></tr
><tr
id=sl_svn887_255

><td class="source">}<br></td></tr
><tr
id=sl_svn887_256

><td class="source">#endif<br></td></tr
><tr
id=sl_svn887_257

><td class="source"><br></td></tr
><tr
id=sl_svn887_258

><td class="source">#endif // _COMPILER_INTERFACE_INCLUDED_<br></td></tr
></table></pre>
<pre><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
</td>
</tr></table>

 
<script type="text/javascript">
 var lineNumUnderMouse = -1;
 
 function gutterOver(num) {
 gutterOut();
 var newTR = document.getElementById('gr_svn887_' + num);
 if (newTR) {
 newTR.className = 'undermouse';
 }
 lineNumUnderMouse = num;
 }
 function gutterOut() {
 if (lineNumUnderMouse != -1) {
 var oldTR = document.getElementById(
 'gr_svn887_' + lineNumUnderMouse);
 if (oldTR) {
 oldTR.className = '';
 }
 lineNumUnderMouse = -1;
 }
 }
 var numsGenState = {table_base_id: 'nums_table_'};
 var srcGenState = {table_base_id: 'src_table_'};
 var alignerRunning = false;
 var startOver = false;
 function setLineNumberHeights() {
 if (alignerRunning) {
 startOver = true;
 return;
 }
 numsGenState.chunk_id = 0;
 numsGenState.table = document.getElementById('nums_table_0');
 numsGenState.row_num = 0;
 if (!numsGenState.table) {
 return; // Silently exit if no file is present.
 }
 srcGenState.chunk_id = 0;
 srcGenState.table = document.getElementById('src_table_0');
 srcGenState.row_num = 0;
 alignerRunning = true;
 continueToSetLineNumberHeights();
 }
 function rowGenerator(genState) {
 if (genState.row_num < genState.table.rows.length) {
 var currentRow = genState.table.rows[genState.row_num];
 genState.row_num++;
 return currentRow;
 }
 var newTable = document.getElementById(
 genState.table_base_id + (genState.chunk_id + 1));
 if (newTable) {
 genState.chunk_id++;
 genState.row_num = 0;
 genState.table = newTable;
 return genState.table.rows[0];
 }
 return null;
 }
 var MAX_ROWS_PER_PASS = 1000;
 function continueToSetLineNumberHeights() {
 var rowsInThisPass = 0;
 var numRow = 1;
 var srcRow = 1;
 while (numRow && srcRow && rowsInThisPass < MAX_ROWS_PER_PASS) {
 numRow = rowGenerator(numsGenState);
 srcRow = rowGenerator(srcGenState);
 rowsInThisPass++;
 if (numRow && srcRow) {
 if (numRow.offsetHeight != srcRow.offsetHeight) {
 numRow.firstChild.style.height = srcRow.offsetHeight + 'px';
 }
 }
 }
 if (rowsInThisPass >= MAX_ROWS_PER_PASS) {
 setTimeout(continueToSetLineNumberHeights, 10);
 } else {
 alignerRunning = false;
 if (startOver) {
 startOver = false;
 setTimeout(setLineNumberHeights, 500);
 }
 }
 }
 function initLineNumberHeights() {
 // Do 2 complete passes, because there can be races
 // between this code and prettify.
 startOver = true;
 setTimeout(setLineNumberHeights, 250);
 window.onresize = setLineNumberHeights;
 }
 initLineNumberHeights();
</script>

 
 
 <div id="log">
 <div style="text-align:right">
 <a class="ifCollapse" href="#" onclick="_toggleMeta(this); return false">Show details</a>
 <a class="ifExpand" href="#" onclick="_toggleMeta(this); return false">Hide details</a>
 </div>
 <div class="ifExpand">
 
 
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="changelog">
 <p>Change log</p>
 <div>
 <a href="/p/gamekit/source/detail?spec=svn887&amp;r=887">r887</a>
 by harkon.kr
 on Apr 24, 2011
 &nbsp; <a href="/p/gamekit/source/diff?spec=svn887&r=887&amp;format=side&amp;path=/trunk/Dependencies/Win32/gles2/include/GLSLANG/ShaderLang.h&amp;old_path=/trunk/Dependencies/Win32/gles2/include/GLSLANG/ShaderLang.h&amp;old=">Diff</a>
 </div>
 <pre>Engine/gles2(unstable)
 - If fixed piped rendering isn't support
by gles2 renderer, create
World/BaseWhite/BaseWhiteNoLighting
material &amp; turn off shadow.
 - Added Windows gles2 library(http://code
.google.com/p/angleproject/).

Ogre
 - version up to <a href="/p/gamekit/source/detail?r=2753">r2753</a>.

Doc
...</pre>
 </div>
 
 
 
 
 
 
 <script type="text/javascript">
 var detail_url = '/p/gamekit/source/detail?r=887&spec=svn887';
 var publish_url = '/p/gamekit/source/detail?r=887&spec=svn887#publish';
 // describe the paths of this revision in javascript.
 var changed_paths = [];
 var changed_urls = [];
 
 changed_paths.push('/trunk/CMake/ConfigOgreKit.cmake');
 changed_urls.push('/p/gamekit/source/browse/trunk/CMake/ConfigOgreKit.cmake?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/CMake/DependenciesOgreKit.cmake');
 changed_urls.push('/p/gamekit/source/browse/trunk/CMake/DependenciesOgreKit.cmake?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/CMake/Packages/FindOpenGLES2.cmake');
 changed_urls.push('/p/gamekit/source/browse/trunk/CMake/Packages/FindOpenGLES2.cmake?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/AUTHORS');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/AUTHORS?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/CONTRIBUTORS');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/CONTRIBUTORS?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/LICENSE');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/LICENSE?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/bin');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/bin?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/bin/libEGL.dll');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/bin/libEGL.dll?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/bin/libGLESv2.dll');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/bin/libGLESv2.dll?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/include');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/include/EGL');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/EGL?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/include/EGL/egl.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/EGL/egl.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/include/EGL/eglext.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/EGL/eglext.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/include/EGL/eglplatform.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/EGL/eglplatform.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/include/GLES2');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/GLES2?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/include/GLES2/gl2.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/GLES2/gl2.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/include/GLES2/gl2ext.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/GLES2/gl2ext.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/include/GLES2/gl2platform.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/GLES2/gl2platform.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/include/GLSLANG');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/GLSLANG?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/include/GLSLANG/ShaderLang.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/GLSLANG/ShaderLang.h?r\x3d887\x26spec\x3dsvn887');
 
 var selected_path = '/trunk/Dependencies/Win32/gles2/include/GLSLANG/ShaderLang.h';
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/include/KHR');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/KHR?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/include/KHR/khrplatform.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/KHR/khrplatform.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/lib');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/lib?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/lib/libEGL.lib');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/lib/libEGL.lib?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/lib/libGLESv2.lib');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/lib/libGLESv2.lib?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Dependencies/Win32/gles2/r618.txt');
 changed_urls.push('/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/r618.txt?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Docs/CppAPI/Source/About.inl');
 changed_urls.push('/p/gamekit/source/browse/trunk/Docs/CppAPI/Source/About.inl?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Docs/FbtAPI/Source/About.inl');
 changed_urls.push('/p/gamekit/source/browse/trunk/Docs/FbtAPI/Source/About.inl?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Docs/LuaAPI/Source/About.inl');
 changed_urls.push('/p/gamekit/source/browse/trunk/Docs/LuaAPI/Source/About.inl?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Engine/External/Ogre/gkOgreMaterialLoader.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Engine/External/Ogre/gkOgreMaterialLoader.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Engine/External/Ogre/gkOgreMaterialLoader.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Engine/External/Ogre/gkOgreMaterialLoader.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Engine/User/RTShaderLib.zip');
 changed_urls.push('/p/gamekit/source/browse/trunk/Engine/User/RTShaderLib.zip?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Engine/User/gkRTShaderTemplates.inl');
 changed_urls.push('/p/gamekit/source/browse/trunk/Engine/User/gkRTShaderTemplates.inl?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Engine/gkEngine.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Engine/gkEngine.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Engine/gkRenderFactory.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Engine/gkRenderFactory.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Engine/gkRenderFactory.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Engine/gkRenderFactory.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Engine/gkResourceGroupManager.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Engine/gkResourceGroupManager.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Engine/gkResourceGroupManager.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Engine/gkResourceGroupManager.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Engine/gkScene.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Engine/gkScene.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Engine/gkUserDefs.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Engine/gkUserDefs.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Engine/gkUserDefs.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Engine/gkUserDefs.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/AUTHORS');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/AUTHORS?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/BuildingOgre.txt');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/BuildingOgre.txt?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/CHANGES');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/CHANGES?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/Components/Paging/include/OgrePageManager.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/Components/Paging/include/OgrePageManager.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/Components/RTShaderSystem/include/OgreShaderCGProgramWriter.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/include/OgreShaderCGProgramWriter.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/Components/RTShaderSystem/include/OgreShaderGLSLESProgramWriter.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/include/OgreShaderGLSLESProgramWriter.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/Components/RTShaderSystem/include/OgreShaderGenerator.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/include/OgreShaderGenerator.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderCGProgramWriter.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderCGProgramWriter.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderExHardwareSkinning.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderExHardwareSkinning.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderExTextureAtlasSampler.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderExTextureAtlasSampler.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderGLSLESProgramProcessor.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderGLSLESProgramProcessor.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderGLSLESProgramWriter.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderGLSLESProgramWriter.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderGenerator.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderGenerator.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderParameter.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderParameter.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/Components/Terrain/src/OgreTerrain.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/Components/Terrain/src/OgreTerrain.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/INSTALL');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/INSTALL?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/CMakeLists.txt');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/CMakeLists.txt?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OSX/OgreConfigDialogImp.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OSX/OgreConfigDialogImp.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OSX/OgreOSXCocoaView.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OSX/OgreOSXCocoaView.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreCompositorInstance.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreCompositorInstance.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreDepthBuffer.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreDepthBuffer.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreExternalTextureSourceManager.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreExternalTextureSourceManager.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreGpuProgramParams.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreGpuProgramParams.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreInstanceManager.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreInstanceManager.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreLight.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreLight.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreMaterial.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreMaterial.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreMesh.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreMesh.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreMovableObject.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreMovableObject.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgrePatchMesh.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgrePatchMesh.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgrePlane.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgrePlane.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgrePlatformInformation.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgrePlatformInformation.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgrePrerequisites.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgrePrerequisites.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreProgressiveMesh.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreProgressiveMesh.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreQuaternion.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreQuaternion.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreRenderSystem.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreRenderSystem.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreRenderable.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreRenderable.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreRoot.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreRoot.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreSceneManager.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreSceneManager.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreSmallVector.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreSmallVector.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreSubMesh.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreSubMesh.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreTexture.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreTexture.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreVector2.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreVector2.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreVector3.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreVector3.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/include/OgreWindowEventUtilities.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreWindowEventUtilities.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OSX/OgreOSXCocoaView.mm');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OSX/OgreOSXCocoaView.mm?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreCompositorInstance.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreCompositorInstance.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreDataStream.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreDataStream.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreDepthBuffer.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreDepthBuffer.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreEntity.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreEntity.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreFont.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreFont.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreGpuProgramParams.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreGpuProgramParams.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreInstanceBatch.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreInstanceBatch.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreInstanceBatchHW.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreInstanceBatchHW.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreInstanceBatchHW_VTF.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreInstanceBatchHW_VTF.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreInstanceBatchVTF.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreInstanceBatchVTF.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreInstanceManager.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreInstanceManager.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreMaterial.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreMaterial.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreMaterialSerializer.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreMaterialSerializer.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreMesh.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreMesh.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgrePatchMesh.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgrePatchMesh.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgrePlane.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgrePlane.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgrePlatformInformation.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgrePlatformInformation.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgrePose.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgrePose.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreProgressiveMesh.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreProgressiveMesh.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreRenderSystem.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreRenderSystem.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreRoot.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreRoot.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreSceneManager.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreSceneManager.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreSmallVector.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreSmallVector.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreSubMesh.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreSubMesh.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/OgreMain/src/OgreWindowEventUtilities.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreWindowEventUtilities.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/PlugIns/ParticleFX/include/OgreAreaEmitter.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/PlugIns/ParticleFX/include/OgreAreaEmitter.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11GpuProgram.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11GpuProgram.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11HLSLProgram.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11HLSLProgram.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11HardwareBuffer.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11HardwareBuffer.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11HardwareVertexBuffer.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11HardwareVertexBuffer.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11RenderToVertexBuffer.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11RenderToVertexBuffer.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11VertexDeclaration.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11VertexDeclaration.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11GpuProgram.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11GpuProgram.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11HLSLProgram.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11HLSLProgram.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11HardwareBuffer.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11HardwareBuffer.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11HardwarePixelBuffer.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11HardwarePixelBuffer.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11HardwareVertexBuffer.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11HardwareVertexBuffer.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11Mappings.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11Mappings.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11RenderSystem.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11RenderSystem.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11RenderToVertexBuffer.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11RenderToVertexBuffer.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11VertexDeclaration.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11VertexDeclaration.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/CMakeLists.txt');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/CMakeLists.txt?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCGLContext.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCGLContext.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCarbonContext.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCarbonContext.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCarbonWindow.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCarbonWindow.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCocoaContext.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCocoaContext.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCocoaView.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCocoaView.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCocoaWindow.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCocoaWindow.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCocoaWindowDelegate.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCocoaWindowDelegate.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXRenderTexture.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXRenderTexture.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXWindow.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXWindow.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/include/OgreGLFrameBufferObject.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OgreGLFrameBufferObject.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/include/OgreGLTexture.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OgreGLTexture.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/src/GLSL/src/OgreGLSLLinkProgramManager.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/GLSL/src/OgreGLSLLinkProgramManager.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/src/GLSL/src/OgreGLSLProgram.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/GLSL/src/OgreGLSLProgram.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXCarbonWindow.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXCarbonWindow.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXCocoaView.mm');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXCocoaView.mm?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXCocoaWindow.mm');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXCocoaWindow.mm?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXCocoaWindowDelegate.mm');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXCocoaWindowDelegate.mm?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXGLSupport.mm');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXGLSupport.mm?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXWindow.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXWindow.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLDepthBuffer.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLDepthBuffer.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLFBORenderTexture.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLFBORenderTexture.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLFrameBufferObject.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLFrameBufferObject.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLHardwareBufferManager.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLHardwareBufferManager.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLHardwarePixelBuffer.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLHardwarePixelBuffer.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLRenderSystem.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLRenderSystem.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLTexture.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLTexture.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/CMakeLists.txt');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/CMakeLists.txt?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/include/EAGL/OgreEAGLESContext.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/include/EAGL/OgreEAGLESContext.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/include/EAGL/OgreEAGLSupport.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/include/EAGL/OgreEAGLSupport.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/include/EAGL/OgreEAGLView.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/include/EAGL/OgreEAGLView.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/include/EAGL/OgreEAGLViewController.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/include/EAGL/OgreEAGLViewController.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/include/EAGL/OgreEAGLWindow.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/include/EAGL/OgreEAGLWindow.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/include/OgreGLESPrerequisites.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/include/OgreGLESPrerequisites.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/src/EAGL/OgreEAGLESContext.mm');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/EAGL/OgreEAGLESContext.mm?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/src/EAGL/OgreEAGLSupport.mm');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/EAGL/OgreEAGLSupport.mm?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/src/EAGL/OgreEAGLView.mm');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/EAGL/OgreEAGLView.mm?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/src/EAGL/OgreEAGLViewController.mm');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/EAGL/OgreEAGLViewController.mm?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/src/EAGL/OgreEAGLWindow.mm');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/EAGL/OgreEAGLWindow.mm?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESFBOMultiRenderTarget.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESFBOMultiRenderTarget.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESFBORenderTexture.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESFBORenderTexture.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESFrameBufferObject.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESFrameBufferObject.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESHardwarePixelBuffer.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESHardwarePixelBuffer.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESPixelFormat.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESPixelFormat.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESRenderSystem.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESRenderSystem.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESTexture.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESTexture.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/CMakeLists.txt');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/CMakeLists.txt?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/include/EAGL/OgreEAGL2Support.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/include/EAGL/OgreEAGL2Support.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/include/EAGL/OgreEAGL2View.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/include/EAGL/OgreEAGL2View.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/include/EAGL/OgreEAGL2ViewController.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/include/EAGL/OgreEAGL2ViewController.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/include/EAGL/OgreEAGL2Window.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/include/EAGL/OgreEAGL2Window.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/include/EAGL/OgreEAGLES2Context.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/include/EAGL/OgreEAGLES2Context.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/include/OgreGLES2Prerequisites.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/include/OgreGLES2Prerequisites.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/include/OgreGLES2RenderSystem.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/include/OgreGLES2RenderSystem.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/src/EAGL/OgreEAGL2Support.mm');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/EAGL/OgreEAGL2Support.mm?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/src/EAGL/OgreEAGL2View.mm');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/EAGL/OgreEAGL2View.mm?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/src/EAGL/OgreEAGL2ViewController.mm');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/EAGL/OgreEAGL2ViewController.mm?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/src/EAGL/OgreEAGL2Window.mm');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/EAGL/OgreEAGL2Window.mm?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/src/EAGL/OgreEAGLES2Context.mm');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/EAGL/OgreEAGLES2Context.mm?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/src/GLSLES/include/OgreGLSLESLinkProgramManager.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/GLSLES/include/OgreGLSLESLinkProgramManager.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/src/GLSLES/include/OgreGLSLESProgram.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/GLSLES/include/OgreGLSLESProgram.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESLinkProgram.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESLinkProgram.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESLinkProgramManager.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESLinkProgramManager.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESProgram.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESProgram.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/src/OgreGLES2HardwareIndexBuffer.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/OgreGLES2HardwareIndexBuffer.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/src/OgreGLES2HardwareVertexBuffer.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/OgreGLES2HardwareVertexBuffer.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/src/OgreGLES2RenderSystem.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/OgreGLES2RenderSystem.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Ogre-1.8/RenderSystems/GLES2/src/OgreGLES2Texture.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/OgreGLES2Texture.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Samples/LuaEditor/Lib/liLuaUtils.cpp');
 changed_urls.push('/p/gamekit/source/browse/trunk/Samples/LuaEditor/Lib/liLuaUtils.cpp?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Samples/LuaEditor/Lib/liUtils.h');
 changed_urls.push('/p/gamekit/source/browse/trunk/Samples/LuaEditor/Lib/liUtils.h?r\x3d887\x26spec\x3dsvn887');
 
 
 changed_paths.push('/trunk/Samples/Runtime/Samples/OgreSimpleGLSLES.blend');
 changed_urls.push('/p/gamekit/source/browse/trunk/Samples/Runtime/Samples/OgreSimpleGLSLES.blend?r\x3d887\x26spec\x3dsvn887');
 
 
 function getCurrentPageIndex() {
 for (var i = 0; i < changed_paths.length; i++) {
 if (selected_path == changed_paths[i]) {
 return i;
 }
 }
 }
 function getNextPage() {
 var i = getCurrentPageIndex();
 if (i < changed_paths.length - 1) {
 return changed_urls[i + 1];
 }
 return null;
 }
 function getPreviousPage() {
 var i = getCurrentPageIndex();
 if (i > 0) {
 return changed_urls[i - 1];
 }
 return null;
 }
 function gotoNextPage() {
 var page = getNextPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoPreviousPage() {
 var page = getPreviousPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoDetailPage() {
 window.location = detail_url;
 }
 function gotoPublishPage() {
 window.location = publish_url;
 }
</script>

 
 <style type="text/css">
 #review_nav {
 border-top: 3px solid white;
 padding-top: 6px;
 margin-top: 1em;
 }
 #review_nav td {
 vertical-align: middle;
 }
 #review_nav select {
 margin: .5em 0;
 }
 </style>
 <div id="review_nav">
 <table><tr><td>Go to:&nbsp;</td><td>
 <select name="files_in_rev" onchange="window.location=this.value">
 
 <option value="/p/gamekit/source/browse/trunk/CMake/ConfigOgreKit.cmake?r=887&amp;spec=svn887"
 
 >/trunk/CMake/ConfigOgreKit.cmake</option>
 
 <option value="/p/gamekit/source/browse/trunk/CMake/DependenciesOgreKit.cmake?r=887&amp;spec=svn887"
 
 >.../CMake/DependenciesOgreKit.cmake</option>
 
 <option value="/p/gamekit/source/browse/trunk/CMake/Packages/FindOpenGLES2.cmake?r=887&amp;spec=svn887"
 
 >...ake/Packages/FindOpenGLES2.cmake</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32?r=887&amp;spec=svn887"
 
 >/trunk/Dependencies/Win32</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2?r=887&amp;spec=svn887"
 
 >/trunk/Dependencies/Win32/gles2</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/AUTHORS?r=887&amp;spec=svn887"
 
 >...Dependencies/Win32/gles2/AUTHORS</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/CONTRIBUTORS?r=887&amp;spec=svn887"
 
 >...dencies/Win32/gles2/CONTRIBUTORS</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/LICENSE?r=887&amp;spec=svn887"
 
 >...Dependencies/Win32/gles2/LICENSE</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/bin?r=887&amp;spec=svn887"
 
 >/trunk/Dependencies/Win32/gles2/bin</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/bin/libEGL.dll?r=887&amp;spec=svn887"
 
 >...ncies/Win32/gles2/bin/libEGL.dll</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/bin/libGLESv2.dll?r=887&amp;spec=svn887"
 
 >...es/Win32/gles2/bin/libGLESv2.dll</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include?r=887&amp;spec=svn887"
 
 >...Dependencies/Win32/gles2/include</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/EGL?r=887&amp;spec=svn887"
 
 >...ndencies/Win32/gles2/include/EGL</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/EGL/egl.h?r=887&amp;spec=svn887"
 
 >...es/Win32/gles2/include/EGL/egl.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/EGL/eglext.h?r=887&amp;spec=svn887"
 
 >...Win32/gles2/include/EGL/eglext.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/EGL/eglplatform.h?r=887&amp;spec=svn887"
 
 >.../gles2/include/EGL/eglplatform.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/GLES2?r=887&amp;spec=svn887"
 
 >...encies/Win32/gles2/include/GLES2</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/GLES2/gl2.h?r=887&amp;spec=svn887"
 
 >.../Win32/gles2/include/GLES2/gl2.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/GLES2/gl2ext.h?r=887&amp;spec=svn887"
 
 >...n32/gles2/include/GLES2/gl2ext.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/GLES2/gl2platform.h?r=887&amp;spec=svn887"
 
 >...les2/include/GLES2/gl2platform.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/GLSLANG?r=887&amp;spec=svn887"
 
 >...cies/Win32/gles2/include/GLSLANG</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/GLSLANG/ShaderLang.h?r=887&amp;spec=svn887"
 selected="selected"
 >...es2/include/GLSLANG/ShaderLang.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/KHR?r=887&amp;spec=svn887"
 
 >...ndencies/Win32/gles2/include/KHR</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/include/KHR/khrplatform.h?r=887&amp;spec=svn887"
 
 >.../gles2/include/KHR/khrplatform.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/lib?r=887&amp;spec=svn887"
 
 >/trunk/Dependencies/Win32/gles2/lib</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/lib/libEGL.lib?r=887&amp;spec=svn887"
 
 >...ncies/Win32/gles2/lib/libEGL.lib</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/lib/libGLESv2.lib?r=887&amp;spec=svn887"
 
 >...es/Win32/gles2/lib/libGLESv2.lib</option>
 
 <option value="/p/gamekit/source/browse/trunk/Dependencies/Win32/gles2/r618.txt?r=887&amp;spec=svn887"
 
 >...ependencies/Win32/gles2/r618.txt</option>
 
 <option value="/p/gamekit/source/browse/trunk/Docs/CppAPI/Source/About.inl?r=887&amp;spec=svn887"
 
 >/trunk/Docs/CppAPI/Source/About.inl</option>
 
 <option value="/p/gamekit/source/browse/trunk/Docs/FbtAPI/Source/About.inl?r=887&amp;spec=svn887"
 
 >/trunk/Docs/FbtAPI/Source/About.inl</option>
 
 <option value="/p/gamekit/source/browse/trunk/Docs/LuaAPI/Source/About.inl?r=887&amp;spec=svn887"
 
 >/trunk/Docs/LuaAPI/Source/About.inl</option>
 
 <option value="/p/gamekit/source/browse/trunk/Engine/External/Ogre/gkOgreMaterialLoader.cpp?r=887&amp;spec=svn887"
 
 >...al/Ogre/gkOgreMaterialLoader.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Engine/External/Ogre/gkOgreMaterialLoader.h?r=887&amp;spec=svn887"
 
 >...rnal/Ogre/gkOgreMaterialLoader.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Engine/User/RTShaderLib.zip?r=887&amp;spec=svn887"
 
 >/trunk/Engine/User/RTShaderLib.zip</option>
 
 <option value="/p/gamekit/source/browse/trunk/Engine/User/gkRTShaderTemplates.inl?r=887&amp;spec=svn887"
 
 >...ine/User/gkRTShaderTemplates.inl</option>
 
 <option value="/p/gamekit/source/browse/trunk/Engine/gkEngine.cpp?r=887&amp;spec=svn887"
 
 >/trunk/Engine/gkEngine.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Engine/gkRenderFactory.cpp?r=887&amp;spec=svn887"
 
 >/trunk/Engine/gkRenderFactory.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Engine/gkRenderFactory.h?r=887&amp;spec=svn887"
 
 >/trunk/Engine/gkRenderFactory.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Engine/gkResourceGroupManager.cpp?r=887&amp;spec=svn887"
 
 >...ngine/gkResourceGroupManager.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Engine/gkResourceGroupManager.h?r=887&amp;spec=svn887"
 
 >.../Engine/gkResourceGroupManager.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Engine/gkScene.cpp?r=887&amp;spec=svn887"
 
 >/trunk/Engine/gkScene.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Engine/gkUserDefs.cpp?r=887&amp;spec=svn887"
 
 >/trunk/Engine/gkUserDefs.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Engine/gkUserDefs.h?r=887&amp;spec=svn887"
 
 >/trunk/Engine/gkUserDefs.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/AUTHORS?r=887&amp;spec=svn887"
 
 >/trunk/Ogre-1.8/AUTHORS</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/BuildingOgre.txt?r=887&amp;spec=svn887"
 
 >/trunk/Ogre-1.8/BuildingOgre.txt</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/CHANGES?r=887&amp;spec=svn887"
 
 >/trunk/Ogre-1.8/CHANGES</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/Components/Paging/include/OgrePageManager.h?r=887&amp;spec=svn887"
 
 >...Paging/include/OgrePageManager.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/include/OgreShaderCGProgramWriter.h?r=887&amp;spec=svn887"
 
 >...lude/OgreShaderCGProgramWriter.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/include/OgreShaderGLSLESProgramWriter.h?r=887&amp;spec=svn887"
 
 >.../OgreShaderGLSLESProgramWriter.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/include/OgreShaderGenerator.h?r=887&amp;spec=svn887"
 
 >...em/include/OgreShaderGenerator.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderCGProgramWriter.cpp?r=887&amp;spec=svn887"
 
 >...rc/OgreShaderCGProgramWriter.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderExHardwareSkinning.cpp?r=887&amp;spec=svn887"
 
 >...OgreShaderExHardwareSkinning.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderExTextureAtlasSampler.cpp?r=887&amp;spec=svn887"
 
 >...eShaderExTextureAtlasSampler.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderGLSLESProgramProcessor.cpp?r=887&amp;spec=svn887"
 
 >...ShaderGLSLESProgramProcessor.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderGLSLESProgramWriter.cpp?r=887&amp;spec=svn887"
 
 >...greShaderGLSLESProgramWriter.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderGenerator.cpp?r=887&amp;spec=svn887"
 
 >...stem/src/OgreShaderGenerator.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/Components/RTShaderSystem/src/OgreShaderParameter.cpp?r=887&amp;spec=svn887"
 
 >...stem/src/OgreShaderParameter.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/Components/Terrain/src/OgreTerrain.cpp?r=887&amp;spec=svn887"
 
 >...ents/Terrain/src/OgreTerrain.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/INSTALL?r=887&amp;spec=svn887"
 
 >/trunk/Ogre-1.8/INSTALL</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/CMakeLists.txt?r=887&amp;spec=svn887"
 
 >...Ogre-1.8/OgreMain/CMakeLists.txt</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OSX/OgreConfigDialogImp.h?r=887&amp;spec=svn887"
 
 >...nclude/OSX/OgreConfigDialogImp.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OSX/OgreOSXCocoaView.h?r=887&amp;spec=svn887"
 
 >...n/include/OSX/OgreOSXCocoaView.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreCompositorInstance.h?r=887&amp;spec=svn887"
 
 >...include/OgreCompositorInstance.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreDepthBuffer.h?r=887&amp;spec=svn887"
 
 >...reMain/include/OgreDepthBuffer.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreExternalTextureSourceManager.h?r=887&amp;spec=svn887"
 
 >...reExternalTextureSourceManager.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreGpuProgramParams.h?r=887&amp;spec=svn887"
 
 >...n/include/OgreGpuProgramParams.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreInstanceManager.h?r=887&amp;spec=svn887"
 
 >...in/include/OgreInstanceManager.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreLight.h?r=887&amp;spec=svn887"
 
 >...1.8/OgreMain/include/OgreLight.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreMaterial.h?r=887&amp;spec=svn887"
 
 >.../OgreMain/include/OgreMaterial.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreMesh.h?r=887&amp;spec=svn887"
 
 >...-1.8/OgreMain/include/OgreMesh.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreMovableObject.h?r=887&amp;spec=svn887"
 
 >...Main/include/OgreMovableObject.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgrePatchMesh.h?r=887&amp;spec=svn887"
 
 >...OgreMain/include/OgrePatchMesh.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgrePlane.h?r=887&amp;spec=svn887"
 
 >...1.8/OgreMain/include/OgrePlane.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgrePlatformInformation.h?r=887&amp;spec=svn887"
 
 >...nclude/OgrePlatformInformation.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgrePrerequisites.h?r=887&amp;spec=svn887"
 
 >...Main/include/OgrePrerequisites.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreProgressiveMesh.h?r=887&amp;spec=svn887"
 
 >...in/include/OgreProgressiveMesh.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreQuaternion.h?r=887&amp;spec=svn887"
 
 >...greMain/include/OgreQuaternion.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreRenderSystem.h?r=887&amp;spec=svn887"
 
 >...eMain/include/OgreRenderSystem.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreRenderable.h?r=887&amp;spec=svn887"
 
 >...greMain/include/OgreRenderable.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreRoot.h?r=887&amp;spec=svn887"
 
 >...-1.8/OgreMain/include/OgreRoot.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreSceneManager.h?r=887&amp;spec=svn887"
 
 >...eMain/include/OgreSceneManager.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreSmallVector.h?r=887&amp;spec=svn887"
 
 >...reMain/include/OgreSmallVector.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreSubMesh.h?r=887&amp;spec=svn887"
 
 >...8/OgreMain/include/OgreSubMesh.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreTexture.h?r=887&amp;spec=svn887"
 
 >...8/OgreMain/include/OgreTexture.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreVector2.h?r=887&amp;spec=svn887"
 
 >...8/OgreMain/include/OgreVector2.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreVector3.h?r=887&amp;spec=svn887"
 
 >...8/OgreMain/include/OgreVector3.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/include/OgreWindowEventUtilities.h?r=887&amp;spec=svn887"
 
 >...clude/OgreWindowEventUtilities.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OSX/OgreOSXCocoaView.mm?r=887&amp;spec=svn887"
 
 >...Main/src/OSX/OgreOSXCocoaView.mm</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreCompositorInstance.cpp?r=887&amp;spec=svn887"
 
 >...n/src/OgreCompositorInstance.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreDataStream.cpp?r=887&amp;spec=svn887"
 
 >.../OgreMain/src/OgreDataStream.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreDepthBuffer.cpp?r=887&amp;spec=svn887"
 
 >...OgreMain/src/OgreDepthBuffer.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreEntity.cpp?r=887&amp;spec=svn887"
 
 >...-1.8/OgreMain/src/OgreEntity.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreFont.cpp?r=887&amp;spec=svn887"
 
 >...re-1.8/OgreMain/src/OgreFont.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreGpuProgramParams.cpp?r=887&amp;spec=svn887"
 
 >...ain/src/OgreGpuProgramParams.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreInstanceBatch.cpp?r=887&amp;spec=svn887"
 
 >...reMain/src/OgreInstanceBatch.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreInstanceBatchHW.cpp?r=887&amp;spec=svn887"
 
 >...Main/src/OgreInstanceBatchHW.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreInstanceBatchHW_VTF.cpp?r=887&amp;spec=svn887"
 
 >.../src/OgreInstanceBatchHW_VTF.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreInstanceBatchVTF.cpp?r=887&amp;spec=svn887"
 
 >...ain/src/OgreInstanceBatchVTF.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreInstanceManager.cpp?r=887&amp;spec=svn887"
 
 >...Main/src/OgreInstanceManager.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreMaterial.cpp?r=887&amp;spec=svn887"
 
 >....8/OgreMain/src/OgreMaterial.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreMaterialSerializer.cpp?r=887&amp;spec=svn887"
 
 >...n/src/OgreMaterialSerializer.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreMesh.cpp?r=887&amp;spec=svn887"
 
 >...re-1.8/OgreMain/src/OgreMesh.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgrePatchMesh.cpp?r=887&amp;spec=svn887"
 
 >...8/OgreMain/src/OgrePatchMesh.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgrePlane.cpp?r=887&amp;spec=svn887"
 
 >...e-1.8/OgreMain/src/OgrePlane.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgrePlatformInformation.cpp?r=887&amp;spec=svn887"
 
 >.../src/OgrePlatformInformation.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgrePose.cpp?r=887&amp;spec=svn887"
 
 >...re-1.8/OgreMain/src/OgrePose.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreProgressiveMesh.cpp?r=887&amp;spec=svn887"
 
 >...Main/src/OgreProgressiveMesh.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreRenderSystem.cpp?r=887&amp;spec=svn887"
 
 >...greMain/src/OgreRenderSystem.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreRoot.cpp?r=887&amp;spec=svn887"
 
 >...re-1.8/OgreMain/src/OgreRoot.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreSceneManager.cpp?r=887&amp;spec=svn887"
 
 >...greMain/src/OgreSceneManager.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreSmallVector.cpp?r=887&amp;spec=svn887"
 
 >...OgreMain/src/OgreSmallVector.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreSubMesh.cpp?r=887&amp;spec=svn887"
 
 >...1.8/OgreMain/src/OgreSubMesh.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/OgreMain/src/OgreWindowEventUtilities.cpp?r=887&amp;spec=svn887"
 
 >...src/OgreWindowEventUtilities.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/PlugIns/ParticleFX/include/OgreAreaEmitter.h?r=887&amp;spec=svn887"
 
 >...icleFX/include/OgreAreaEmitter.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11GpuProgram.h?r=887&amp;spec=svn887"
 
 >...11/include/OgreD3D11GpuProgram.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11HLSLProgram.h?r=887&amp;spec=svn887"
 
 >...1/include/OgreD3D11HLSLProgram.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11HardwareBuffer.h?r=887&amp;spec=svn887"
 
 >...nclude/OgreD3D11HardwareBuffer.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11HardwareVertexBuffer.h?r=887&amp;spec=svn887"
 
 >.../OgreD3D11HardwareVertexBuffer.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11RenderToVertexBuffer.h?r=887&amp;spec=svn887"
 
 >.../OgreD3D11RenderToVertexBuffer.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/include/OgreD3D11VertexDeclaration.h?r=887&amp;spec=svn887"
 
 >...ude/OgreD3D11VertexDeclaration.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11GpuProgram.cpp?r=887&amp;spec=svn887"
 
 >...3D11/src/OgreD3D11GpuProgram.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11HLSLProgram.cpp?r=887&amp;spec=svn887"
 
 >...D11/src/OgreD3D11HLSLProgram.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11HardwareBuffer.cpp?r=887&amp;spec=svn887"
 
 >.../src/OgreD3D11HardwareBuffer.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11HardwarePixelBuffer.cpp?r=887&amp;spec=svn887"
 
 >...OgreD3D11HardwarePixelBuffer.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11HardwareVertexBuffer.cpp?r=887&amp;spec=svn887"
 
 >...greD3D11HardwareVertexBuffer.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11Mappings.cpp?r=887&amp;spec=svn887"
 
 >...ct3D11/src/OgreD3D11Mappings.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11RenderSystem.cpp?r=887&amp;spec=svn887"
 
 >...11/src/OgreD3D11RenderSystem.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11RenderToVertexBuffer.cpp?r=887&amp;spec=svn887"
 
 >...greD3D11RenderToVertexBuffer.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/Direct3D11/src/OgreD3D11VertexDeclaration.cpp?r=887&amp;spec=svn887"
 
 >...c/OgreD3D11VertexDeclaration.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/CMakeLists.txt?r=887&amp;spec=svn887"
 
 >.../RenderSystems/GL/CMakeLists.txt</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCGLContext.h?r=887&amp;spec=svn887"
 
 >.../include/OSX/OgreOSXCGLContext.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCarbonContext.h?r=887&amp;spec=svn887"
 
 >...clude/OSX/OgreOSXCarbonContext.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCarbonWindow.h?r=887&amp;spec=svn887"
 
 >...nclude/OSX/OgreOSXCarbonWindow.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCocoaContext.h?r=887&amp;spec=svn887"
 
 >...nclude/OSX/OgreOSXCocoaContext.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCocoaView.h?r=887&amp;spec=svn887"
 
 >...L/include/OSX/OgreOSXCocoaView.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCocoaWindow.h?r=887&amp;spec=svn887"
 
 >...include/OSX/OgreOSXCocoaWindow.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXCocoaWindowDelegate.h?r=887&amp;spec=svn887"
 
 >...OSX/OgreOSXCocoaWindowDelegate.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXRenderTexture.h?r=887&amp;spec=svn887"
 
 >...clude/OSX/OgreOSXRenderTexture.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OSX/OgreOSXWindow.h?r=887&amp;spec=svn887"
 
 >...s/GL/include/OSX/OgreOSXWindow.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OgreGLFrameBufferObject.h?r=887&amp;spec=svn887"
 
 >...nclude/OgreGLFrameBufferObject.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/include/OgreGLTexture.h?r=887&amp;spec=svn887"
 
 >...stems/GL/include/OgreGLTexture.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/GLSL/src/OgreGLSLLinkProgramManager.cpp?r=887&amp;spec=svn887"
 
 >...c/OgreGLSLLinkProgramManager.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/GLSL/src/OgreGLSLProgram.cpp?r=887&amp;spec=svn887"
 
 >...src/GLSL/src/OgreGLSLProgram.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXCarbonWindow.cpp?r=887&amp;spec=svn887"
 
 >.../src/OSX/OgreOSXCarbonWindow.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXCocoaView.mm?r=887&amp;spec=svn887"
 
 >...s/GL/src/OSX/OgreOSXCocoaView.mm</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXCocoaWindow.mm?r=887&amp;spec=svn887"
 
 >...GL/src/OSX/OgreOSXCocoaWindow.mm</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXCocoaWindowDelegate.mm?r=887&amp;spec=svn887"
 
 >...SX/OgreOSXCocoaWindowDelegate.mm</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXGLSupport.mm?r=887&amp;spec=svn887"
 
 >...s/GL/src/OSX/OgreOSXGLSupport.mm</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OSX/OgreOSXWindow.cpp?r=887&amp;spec=svn887"
 
 >...ems/GL/src/OSX/OgreOSXWindow.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLDepthBuffer.cpp?r=887&amp;spec=svn887"
 
 >...ems/GL/src/OgreGLDepthBuffer.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLFBORenderTexture.cpp?r=887&amp;spec=svn887"
 
 >...L/src/OgreGLFBORenderTexture.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLFrameBufferObject.cpp?r=887&amp;spec=svn887"
 
 >.../src/OgreGLFrameBufferObject.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLHardwareBufferManager.cpp?r=887&amp;spec=svn887"
 
 >.../OgreGLHardwareBufferManager.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLHardwarePixelBuffer.cpp?r=887&amp;spec=svn887"
 
 >...rc/OgreGLHardwarePixelBuffer.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLRenderSystem.cpp?r=887&amp;spec=svn887"
 
 >...ms/GL/src/OgreGLRenderSystem.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GL/src/OgreGLTexture.cpp?r=887&amp;spec=svn887"
 
 >...Systems/GL/src/OgreGLTexture.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/CMakeLists.txt?r=887&amp;spec=svn887"
 
 >...enderSystems/GLES/CMakeLists.txt</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/include/EAGL/OgreEAGLESContext.h?r=887&amp;spec=svn887"
 
 >...include/EAGL/OgreEAGLESContext.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/include/EAGL/OgreEAGLSupport.h?r=887&amp;spec=svn887"
 
 >...S/include/EAGL/OgreEAGLSupport.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/include/EAGL/OgreEAGLView.h?r=887&amp;spec=svn887"
 
 >...GLES/include/EAGL/OgreEAGLView.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/include/EAGL/OgreEAGLViewController.h?r=887&amp;spec=svn887"
 
 >...de/EAGL/OgreEAGLViewController.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/include/EAGL/OgreEAGLWindow.h?r=887&amp;spec=svn887"
 
 >...ES/include/EAGL/OgreEAGLWindow.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/include/OgreGLESPrerequisites.h?r=887&amp;spec=svn887"
 
 >.../include/OgreGLESPrerequisites.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/EAGL/OgreEAGLESContext.mm?r=887&amp;spec=svn887"
 
 >...ES/src/EAGL/OgreEAGLESContext.mm</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/EAGL/OgreEAGLSupport.mm?r=887&amp;spec=svn887"
 
 >...GLES/src/EAGL/OgreEAGLSupport.mm</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/EAGL/OgreEAGLView.mm?r=887&amp;spec=svn887"
 
 >...ms/GLES/src/EAGL/OgreEAGLView.mm</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/EAGL/OgreEAGLViewController.mm?r=887&amp;spec=svn887"
 
 >...c/EAGL/OgreEAGLViewController.mm</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/EAGL/OgreEAGLWindow.mm?r=887&amp;spec=svn887"
 
 >.../GLES/src/EAGL/OgreEAGLWindow.mm</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESFBOMultiRenderTarget.cpp?r=887&amp;spec=svn887"
 
 >...OgreGLESFBOMultiRenderTarget.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESFBORenderTexture.cpp?r=887&amp;spec=svn887"
 
 >...src/OgreGLESFBORenderTexture.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESFrameBufferObject.cpp?r=887&amp;spec=svn887"
 
 >...rc/OgreGLESFrameBufferObject.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESHardwarePixelBuffer.cpp?r=887&amp;spec=svn887"
 
 >.../OgreGLESHardwarePixelBuffer.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESPixelFormat.cpp?r=887&amp;spec=svn887"
 
 >...GLES/src/OgreGLESPixelFormat.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESRenderSystem.cpp?r=887&amp;spec=svn887"
 
 >...LES/src/OgreGLESRenderSystem.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES/src/OgreGLESTexture.cpp?r=887&amp;spec=svn887"
 
 >...ems/GLES/src/OgreGLESTexture.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/CMakeLists.txt?r=887&amp;spec=svn887"
 
 >...nderSystems/GLES2/CMakeLists.txt</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/include/EAGL/OgreEAGL2Support.h?r=887&amp;spec=svn887"
 
 >.../include/EAGL/OgreEAGL2Support.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/include/EAGL/OgreEAGL2View.h?r=887&amp;spec=svn887"
 
 >...ES2/include/EAGL/OgreEAGL2View.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/include/EAGL/OgreEAGL2ViewController.h?r=887&amp;spec=svn887"
 
 >...e/EAGL/OgreEAGL2ViewController.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/include/EAGL/OgreEAGL2Window.h?r=887&amp;spec=svn887"
 
 >...2/include/EAGL/OgreEAGL2Window.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/include/EAGL/OgreEAGLES2Context.h?r=887&amp;spec=svn887"
 
 >...nclude/EAGL/OgreEAGLES2Context.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/include/OgreGLES2Prerequisites.h?r=887&amp;spec=svn887"
 
 >...include/OgreGLES2Prerequisites.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/include/OgreGLES2RenderSystem.h?r=887&amp;spec=svn887"
 
 >.../include/OgreGLES2RenderSystem.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/EAGL/OgreEAGL2Support.mm?r=887&amp;spec=svn887"
 
 >...ES2/src/EAGL/OgreEAGL2Support.mm</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/EAGL/OgreEAGL2View.mm?r=887&amp;spec=svn887"
 
 >.../GLES2/src/EAGL/OgreEAGL2View.mm</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/EAGL/OgreEAGL2ViewController.mm?r=887&amp;spec=svn887"
 
 >.../EAGL/OgreEAGL2ViewController.mm</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/EAGL/OgreEAGL2Window.mm?r=887&amp;spec=svn887"
 
 >...LES2/src/EAGL/OgreEAGL2Window.mm</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/EAGL/OgreEAGLES2Context.mm?r=887&amp;spec=svn887"
 
 >...2/src/EAGL/OgreEAGLES2Context.mm</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/GLSLES/include/OgreGLSLESLinkProgramManager.h?r=887&amp;spec=svn887"
 
 >...e/OgreGLSLESLinkProgramManager.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/GLSLES/include/OgreGLSLESProgram.h?r=887&amp;spec=svn887"
 
 >...SLES/include/OgreGLSLESProgram.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESLinkProgram.cpp?r=887&amp;spec=svn887"
 
 >...ES/src/OgreGLSLESLinkProgram.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESLinkProgramManager.cpp?r=887&amp;spec=svn887"
 
 >...OgreGLSLESLinkProgramManager.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/GLSLES/src/OgreGLSLESProgram.cpp?r=887&amp;spec=svn887"
 
 >...GLSLES/src/OgreGLSLESProgram.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/OgreGLES2HardwareIndexBuffer.cpp?r=887&amp;spec=svn887"
 
 >...OgreGLES2HardwareIndexBuffer.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/OgreGLES2HardwareVertexBuffer.cpp?r=887&amp;spec=svn887"
 
 >...greGLES2HardwareVertexBuffer.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/OgreGLES2RenderSystem.cpp?r=887&amp;spec=svn887"
 
 >...S2/src/OgreGLES2RenderSystem.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Ogre-1.8/RenderSystems/GLES2/src/OgreGLES2Texture.cpp?r=887&amp;spec=svn887"
 
 >...s/GLES2/src/OgreGLES2Texture.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Samples/LuaEditor/Lib/liLuaUtils.cpp?r=887&amp;spec=svn887"
 
 >...les/LuaEditor/Lib/liLuaUtils.cpp</option>
 
 <option value="/p/gamekit/source/browse/trunk/Samples/LuaEditor/Lib/liUtils.h?r=887&amp;spec=svn887"
 
 >.../Samples/LuaEditor/Lib/liUtils.h</option>
 
 <option value="/p/gamekit/source/browse/trunk/Samples/Runtime/Samples/OgreSimpleGLSLES.blend?r=887&amp;spec=svn887"
 
 >...e/Samples/OgreSimpleGLSLES.blend</option>
 
 </select>
 </td></tr></table>
 
 
 



 
 </div>
 
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="older_bubble">
 <p>Older revisions</p>
 
 <a href="/p/gamekit/source/list?path=/trunk/Dependencies/Win32/gles2/include/GLSLANG/ShaderLang.h&start=887">All revisions of this file</a>
 </div>
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="fileinfo_bubble">
 <p>File info</p>
 
 <div>Size: 9910 bytes,
 258 lines</div>
 
 <div><a href="//gamekit.googlecode.com/svn-history/r887/trunk/Dependencies/Win32/gles2/include/GLSLANG/ShaderLang.h">View raw file</a></div>
 </div>
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 </div>
 </div>


</div>

</div>
</div>

<script src="http://www.gstatic.com/codesite/ph/3427079965498762429/js/prettify/prettify.js"></script>
<script type="text/javascript">prettyPrint();</script>


<script src="http://www.gstatic.com/codesite/ph/3427079965498762429/js/source_file_scripts.js"></script>

 <script type="text/javascript" src="http://www.gstatic.com/codesite/ph/3427079965498762429/js/kibbles.js"></script>
 <script type="text/javascript">
 var lastStop = null;
 var initialized = false;
 
 function updateCursor(next, prev) {
 if (prev && prev.element) {
 prev.element.className = 'cursor_stop cursor_hidden';
 }
 if (next && next.element) {
 next.element.className = 'cursor_stop cursor';
 lastStop = next.index;
 }
 }
 
 function pubRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initialized) {
 reloadCursors();
 }
 }
 
 function draftRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initialized) {
 reloadCursors();
 }
 }
 
 function draftDestroyed(data) {
 updateCursorForCell(data.cellId, 'nocursor');
 if (initialized) {
 reloadCursors();
 }
 }
 function reloadCursors() {
 kibbles.skipper.reset();
 loadCursors();
 if (lastStop != null) {
 kibbles.skipper.setCurrentStop(lastStop);
 }
 }
 // possibly the simplest way to insert any newly added comments
 // is to update the class of the corresponding cursor row,
 // then refresh the entire list of rows.
 function updateCursorForCell(cellId, className) {
 var cell = document.getElementById(cellId);
 // we have to go two rows back to find the cursor location
 var row = getPreviousElement(cell.parentNode);
 row.className = className;
 }
 // returns the previous element, ignores text nodes.
 function getPreviousElement(e) {
 var element = e.previousSibling;
 if (element.nodeType == 3) {
 element = element.previousSibling;
 }
 if (element && element.tagName) {
 return element;
 }
 }
 function loadCursors() {
 // register our elements with skipper
 var elements = CR_getElements('*', 'cursor_stop');
 var len = elements.length;
 for (var i = 0; i < len; i++) {
 var element = elements[i]; 
 element.className = 'cursor_stop cursor_hidden';
 kibbles.skipper.append(element);
 }
 }
 function toggleComments() {
 CR_toggleCommentDisplay();
 reloadCursors();
 }
 function keysOnLoadHandler() {
 // setup skipper
 kibbles.skipper.addStopListener(
 kibbles.skipper.LISTENER_TYPE.PRE, updateCursor);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_top', 50);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_bottom', 100);
 // Register our keys
 kibbles.skipper.addFwdKey("n");
 kibbles.skipper.addRevKey("p");
 kibbles.keys.addKeyPressListener(
 'u', function() { window.location = detail_url; });
 kibbles.keys.addKeyPressListener(
 'r', function() { window.location = detail_url + '#publish'; });
 
 kibbles.keys.addKeyPressListener('j', gotoNextPage);
 kibbles.keys.addKeyPressListener('k', gotoPreviousPage);
 
 
 }
 </script>
<script src="http://www.gstatic.com/codesite/ph/3427079965498762429/js/code_review_scripts.js"></script>
<script type="text/javascript">
 function showPublishInstructions() {
 var element = document.getElementById('review_instr');
 if (element) {
 element.className = 'opened';
 }
 }
 var codereviews;
 function revsOnLoadHandler() {
 // register our source container with the commenting code
 var paths = {'svn887': '/trunk/Dependencies/Win32/gles2/include/GLSLANG/ShaderLang.h'}
 codereviews = CR_controller.setup(
 {"projectHomeUrl": "/p/gamekit", "loggedInUserEmail": "heinsteinh@gmail.com", "token": "X1eqbq8kTawg_LR6OVnbehjqPTI:1398845685991", "domainName": null, "profileUrl": "/u/112241180151938862863/", "projectName": "gamekit", "assetVersionPath": "http://www.gstatic.com/codesite/ph/3427079965498762429", "relativeBaseUrl": "", "assetHostPath": "http://www.gstatic.com/codesite/ph"}, '', 'svn887', paths,
 CR_BrowseIntegrationFactory);
 
 codereviews.registerActivityListener(CR_ActivityType.REVEAL_DRAFT_PLATE, showPublishInstructions);
 
 codereviews.registerActivityListener(CR_ActivityType.REVEAL_PUB_PLATE, pubRevealed);
 codereviews.registerActivityListener(CR_ActivityType.REVEAL_DRAFT_PLATE, draftRevealed);
 codereviews.registerActivityListener(CR_ActivityType.DISCARD_DRAFT_COMMENT, draftDestroyed);
 
 
 
 
 
 
 
 var initialized = true;
 reloadCursors();
 }
 window.onload = function() {keysOnLoadHandler(); revsOnLoadHandler();};

</script>
<script type="text/javascript" src="http://www.gstatic.com/codesite/ph/3427079965498762429/js/dit_scripts.js"></script>

 
 
 
 <script type="text/javascript" src="http://www.gstatic.com/codesite/ph/3427079965498762429/js/ph_core.js"></script>
 
 
 
 
</div> 

<div id="footer" dir="ltr">
 <div class="text">
 <a href="/projecthosting/terms.html">Terms</a> -
 <a href="http://www.google.com/privacy.html">Privacy</a> -
 <a href="/p/support/">Project Hosting Help</a>
 </div>
</div>
 <div class="hostedBy" style="margin-top: -20px;">
 <span style="vertical-align: top;">Powered by <a href="http://code.google.com/projecthosting/">Google Project Hosting</a></span>
 </div>

 
 


 
 </body>
</html>

