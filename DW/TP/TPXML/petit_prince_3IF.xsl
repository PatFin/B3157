<?xml version="1.0" encoding="UTF-8"?>

<!-- New document created with EditiX at Mon Apr 04 15:06:59 CEST 2016 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:output method="html"/>
	
	<xsl:template match="/">
	<html>
		<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
			<title>
			<xsl:value-of select="//titre"/>
			<xsl:text> de </xsl:text>
			
<xsl:value-of select="//auteur"/>
			</title>
		</head>
		<body style="background-color:white;">
			<table align="center" cellspacing="50">
				<tbody>
					<tr>
					<td>
						<xsl:apply-templates select="//image"/>
					</td>
					<td>
					<h1 style="text-align:center; color:blue;">
						<xsl:value-of select="//titre"/>
					</h1>
					<xsl:apply-templates select="//infos/auteur"/>
					<xsl:apply-templates select="//infos"/>
					
				</td>
			</tr>
		</tbody>
		</table>
			<hr/>
			
			<xsl:apply-templates select="//paragr"/>
		</body>
	</html>
	</xsl:template>


	<xsl:template match="auteur">

		<h2 style="text-align:center; font-style: italic;">

		<xsl:value-of select="//auteur"/>
		</h2>
	

	</xsl:template>

	

	<xsl:template match="infos">

		<blockquote style="color:darkgreen">

		<xsl:text>But du TP du </xsl:text>

		<xsl:value-of select="//infos/date"/>

		<xsl:text>:  </xsl:text>

		<xsl:value-of select="//infos/but"/>

		<br/>

		<xsl:text>Auteurs: </xsl:text>

		

		<xsl:for-each select="//infos/mise_en_forme_par/auteur">

			<xsl:value-of select="."/>

			

			

			<xsl:if test ="not(.=//infos/mise_en_forme_par/auteur[position()=last()])">

				<xsl:text> et </xsl:text>

			</xsl:if>

				

		</xsl:for-each>

		<xsl:text> (</xsl:text>

		<xsl:value-of select="//infos/mise_en_forme_par/auteur/@NoBinome"/>

		<xsl:text>)</xsl:text>

		<br/>

		<xsl:text>Email du responsable: </xsl:text>

		<xsl:value-of select="//email"/>	

			

		</blockquote>

	</xsl:template>

	

	<xsl:template match="image">
		
<div align="center">
			<img>
			<xsl:attribute name="src">
			<xsl:value-of select="//couverture/@chemin"/>
			</xsl:attribute>
			</img>
		</div>

	</xsl:template>

	

	<xsl:template match="corps">


		<xsl:value-of select="//corps"/>

	

	</xsl:template>

	

	<xsl:template match="paragr ">

		
		<p>
			<xsl:apply-templates/>
		</p>

	</xsl:template>

	

	<xsl:template match="paragr[@type='narration']/phrase">

	
		<xsl:if test="./@langue = 'fr' ">
	
			<span style="">
	
				<xsl:value-of select="."/>
	
			</span>
	
		</xsl:if>
	
		
	
		<xsl:if test="./@langue = 'hu' ">
	
			<xsl:if test="./preceding-sibling::phrase[1]/@langue = 'fr'">
	
				<br/>
	
			</xsl:if>
	
			<span style="font-style: italic; color: brown;">
	
				<xsl:value-of select="."/>
	
			</span>
	
		</xsl:if>

	</xsl:template>

	

	
<xsl:template match="paragr[@type='dialogue']/phrase">

	

	
	


	</xsl:template>

	


</xsl:stylesheet>
