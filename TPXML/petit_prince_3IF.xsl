<?xml version="1.0" encoding="UTF-8"?>

<!-- New document created with EditiX at Mon Apr 04 15:06:59 CEST 2016 -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:output method="html"/>
	
	<xsl:template match="/">
	<html>
		<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
		
		<!-- Affichage du titre de la page HTML -->
		<title>
			<xsl:value-of select="//titre"/>
			<xsl:text> de </xsl:text>
			
			<xsl:value-of select="//auteur"/>

		</title>
		</head>
		
		<body style="background-color:white;">
		
		
			      
 <xsl:apply-templates/>
			
			      <!-- Affichage de la fin du texte -->
			      <h3>Fin du texte.</h3>
			      <hr/> <!-- affichage d une ligne horizontale --> 
		</body>
	</html>
	
	</xsl:template>


	<xsl:template match="entete">
	
<!-- Affichage des informations -->	 
		<table align="center" cellspacing="50">
			<tbody>
				<tr>
					<td>
						<img src="images/prince.png"/>
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
			<!-- affichage d une ligne horizontale --> 
			<hr/>

			<!-- Affichage du début du texte -->
			      <h3>Début du texte:</h3>
		

	</xsl:template>

	<xsl:template match="auteur">
	
		<h2 style="text-align:center; font-style: italic;">
		<xsl:value-of select="//auteur"/>
		</h2>
		
	</xsl:template>

	

  <!-- Affichage des infos en en tête -->
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
			<xsl:choose>
			        <xsl:when test="not(.=//infos/mise_en_forme_par/auteur[position()=last()])">
			          	<xsl:if test ="not(contains(string(./@NoBinome),string(following-sibling::*[1]/@NoBinome)))">
					<xsl:text> (</xsl:text>
					<xsl:value-of select="./@NoBinome"/>
			
					<xsl:text>) </xsl:text>
				</xsl:if>
				<xsl:text> et </xsl:text>
			        </xsl:when>
			        <xsl:otherwise>
			          
				<xsl:text> (</xsl:text>
				<xsl:value-of select="./@NoBinome"/>
		
				<xsl:text>)</xsl:text>
			
			        </xsl:otherwise>
			 </xsl:choose>
			
			<xsl:if test ="not(.=//infos/mise_en_forme_par/auteur[position()=last()])">
				
			</xsl:if>
		</xsl:for-each>

		<br/>
		<xsl:text>Email du responsable: </xsl:text>
		<xsl:value-of select="//email"/>	
		</blockquote>
		
	</xsl:template>

	

  <!-- Affichage des image du xml -->
	<xsl:template match="image">
		
		<div align="center">
			<img>
			<xsl:attribute name="src">
			<xsl:value-of select="@chemin"/>
			</xsl:attribute>
			</img>
		</div>

	</xsl:template>

	

  <!-- Affichage des phrases de narration -->
	<xsl:template match="paragr[@type='narration']">

		

		<p>
		<xsl:for-each select="./phrase[@langue = 'fr'] ">
			<span style="">
				 <xsl:choose>
					<xsl:when test="contains(.,'mouton')">
					  <span style="font-size: 24px; font-weight: bold;">
						<xsl:value-of select="."/> 
						<img src="images/moutonDessin.png"/>
					  </span>
					</xsl:when>
					<xsl:otherwise>
					  <xsl:value-of select="."/> 
					</xsl:otherwise>
				  </xsl:choose>  
			</span>
	
		</xsl:for-each>
		
<br/>
		<xsl:for-each select="./phrase[@langue = 'hu'] ">
			<span style="font-style: italic; color: brown;">
				<xsl:value-of select="."/>
			</span>
		</xsl:for-each>
		</p>

	</xsl:template>

	


  <!-- Affichage des dialogues des personnages dans un tableau avec leur image -->
  <xsl:template match="paragr[@type='dialogue']">
  
   <table width="90%" align="center">
		<tbody>
		  <tr>
			  <!-- Tableau de dialogue en francais -->
			  <td width="45%">
				<table border="1" width="100%" cellpadding="10">
				  <xsl:for-each select="phrase[@langue='fr']">
					<tbody>
					  <tr>
						<td width="50">
						  <img src="images/{@locuteur}.png"/>
						</td>
						<td> 
						  <!-- Verifier l ajout d un mouton -->
						  <xsl:choose>
							<xsl:when test="contains(.,'mouton')">
							  <span style="font-size: 24px; font-weight: bold;">
								<xsl:value-of select="."/> 
								<img src="images/moutonDessin.png"/>
							  </span>
							</xsl:when>
							<xsl:otherwise>
							  <xsl:value-of select="."/> 
							</xsl:otherwise>
						  </xsl:choose>  
						  
						</td>
					  </tr>
					</tbody>
				  </xsl:for-each>
				</table>
			  </td>
			  <td></td>
			  
			  <!-- Tableau de dialogue en hongrois -->
			  <td width="45%">
				<table border="1" width="100%" cellpadding="10">
				  <xsl:for-each select="phrase[@langue='hu']">
					<tbody>
					  <tr>
						<td width="50">
						  <img src="images/{@locuteur}.png"/>
						</td>
						<td>
						  <span style="font-style: italic; color: brown;">
								<xsl:value-of select="."/> 

						  </span>
						</td>
					  </tr>
					</tbody>
				  </xsl:for-each>
				</table>
			  </td>
		  </tr>
		</tbody>
    </table> 
    
  </xsl:template>

</xsl:stylesheet>
