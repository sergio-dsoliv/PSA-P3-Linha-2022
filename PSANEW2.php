<!-- Interface web -->
<html>
    <body>



    
            <!--Criação das imagens,textboxes, botões e labels presentes na interface web   -->
        <div id="container">

            <header>
        
            <div class="logo"> 
                
                <img src="logo2.png" alt="UNIVERSIDADE DE AVEIRO" style="margin-left: 100px;" > 
                
            </div>
            </header>
            <br>
            <br>
            <div class="linha">
        
                <img src="linha2.png" alt="LINHA DE TRANFERÊNCIA" style="width:400px;heigth:75px;margin-top:-50px;margin-left:-10px;" >

            </div>
        
            <!-- Forms para atualizaçao da página  -->
            <div class="forma" style= "text-align:center;"> Ordem <br>       
            
            <label id= "palete"> Palete </label>  
            <input type="text" name="Palete" id="PALETE" value=0  placeholder="Numero da palete" >
            <label id= "destino"> Destino </label>          
            <input type="text" name="Destino"  id="DESTINO" value=0 placeholder="Barragem de destino" ><br>
            <input type="submit" name="mover" id="mover">
            </div>
            <div class="boxes">
            <label id= "distribuicao"> Distribuição </label><br><br> 
            <label id= "aguardar"> Aguadar </label><br><br> 
            <label id= "operacao"> Operação </label> 
            </div>
            
            <?php 
        
            //Definição de variaveis 
            
            $Y1=$_POST['Palete'];
            $Y2=$_POST['Destino'];
            $Y0=$_POST['mover'];
        
        
            //Conectando, escolhendo o banco de dados 
            $link = mysqli_connect("localhost", "root", "0000")or die("Nao pude conectar: " . mysqli_error());
            mysqli_select_db($link,"psa") or die("Nao pude selecionar o banco de dados");
            // Query SQL de actualizacao 
            $query = "UPDATE estado SET Palete='" . $Y1 . "' , Posicao='". $Y2 ."', Start='". $Y0 ."' WHERE id=1";
            $result = mysqli_query($link,$query) or die("A query falhou: " . mysqli_error());
                    // Fazendo a query SQL DE LEITURA DA BASE DE DADOS
            $query = "SELECT * FROM estado";
            $result = mysqli_query($link,$query) or die("A query falhou: " . mysqli_error());
            $linha1=mysqli_fetch_array($result,MYSQLI_ASSOC);
    // registo de dados na base 
            $palete="Palete: ".$linha1['Palete'];
            $destino=" Destino: ".$linha1['Posicao']; 
        //Definição da informação na tabela     
            $table  = '<table>';
            $table .= '<thead>';
            $table .= '<tr>';
            $table .= '<td>Palete 1</td>';
            $table .= "<td>{$linha1['Palete1']}</td>";
            $table .= '</tr>';
            $table .= '<tr>';
            $table .= '<td>Palete 2</td>';
            $table .= "<td>{$linha1['Palete2']}</td>";
            $table .= '</tr>';
            $table .= '<tr>';
            $table .= '<td>Palete 3</td>';
            $table .= "<td>{$linha1['Palete3']}</td>";
            $table .= '</tr>';
            $table .= '<tr>';
            $table .= '<td>Palete 4</td>';
            $table .= "<td>{$linha1['Palete4']}</td>";
            $table .= '</tr>';
            $table .= '<tr>';
            $table .= '<td>Palete 5</td>';
            $table .= "<td>{$linha1['Palete5']}</td>";
            $table .= '</tr>';
            $table .= '<tr>';
            $table .= '<td>Palete 6</td>';
            $table .= "<td>{$linha1['Palete6']}</td>";
            $table .= '</tr>';

    
            $table .= '</table>';
            // exibição na tela
            echo $table;
                 

        
            if($linha1['Distribuicao']==1){
            $pagina1= " <br><input type='checkbox' name='Destino' value='checked' style='margin-left:350px;' checked > ";
            } else { 
                $pagina1= "<br><input type='checkbox' name='Destino' value='checked' style='margin-left:350px;' >  ";
            }

            if($linha1['Aguardar']==1){
                $pagina2=  " <input type='checkbox'  value='checked' style='margin-left:350px;margin-top:14px;'  checked > ";
            } else { 
                $pagina2=  "<input type='checkbox'  value='checked'  style='margin-left:350px;margin-top:14px;' >  ";
            }
            if($linha1['X1']==1){
                $pagina3=  " <br><input type='checkbox'  value='checked'  style='margin-left:-105px;margin-top:-160px;' checked > ";
            } else { 
                $pagina3=  " <br><input type='checkbox' value='checked' style='margin-left:-105px;margin-top:-160px;'> ";
            }
            if($linha1['X2']==1){
                $pagina4=  " <br><input type='checkbox'  value='checked'  style='margin-left:0px;margin-top:-150px;' checked > ";
            } else { 
                $pagina4=  " <br><input type='checkbox' value='checked' style='margin-left:0px;margin-top:-150px;'> ";
            }
            if($linha1['X3']==1){
                $pagina5=  " <br><input type='checkbox'  value='checked' style='margin-left: 100px;margin-top:-100px;'  checked > ";
            } else { 
                $pagina5=  " <br><input type='checkbox' value='checked' style='margin-left:100px;margin-top:-100px;'> ";
            }
            if($linha1['X4']==1){
                $pagina6=  " <br><input type='checkbox'  value='checked' style='margin-left:100px;margin-top:-60px;'  checked > ";
            } else { 
                $pagina6= " <br><input type='checkbox' value='checked'style='margin-left:100px;margin-top:-60px;' > ";
            }
            if($linha1['X5']==1){
                $pagina7= " <br><input type='checkbox'  value='checked' style='margin-left:-20px;margin-top:-70px;'  checked > ";
            } else { 
                $pagina7=  " <br><input type='checkbox' value='checked'style='margin-left:-20px;margin-top:-70px;' > ";
            }
            if($linha1['X6']==1){
                $pagina8=  " <br><input type='checkbox'  value='checked'  style='margin-left:-125px;margin-top:-125px;' checked > ";
            } else { 
                $pagina8=  " <br><input type='checkbox' value='checked'style='margin-left:-125px;margin-top:-125px;' > ";
            }
            if($linha1['Operacao']==1){
                $pagina9=  " <input type='checkbox'  value='checked'   style='margin-left:350px;margin-top:10px;' checked > ";
            } else { 
                $pagina9=  "<input type='checkbox'  value='checked'   style='margin-left:350px;margin-top:10px;' >  ";
            }

        
            //Update 

            if($linha1['Distribuicao']){
                $Y3='Distribuição';

            }elseif($linha1['Aguardar']){
                $Y3='Aguardar'; 

            }elseif($linha1['Operacao']){
                $Y3='Operacao'; 

            }
        
            $sql="INSERT INTO registo_de_dados (Operação, Palete, Destino,Palete1,Palete2,Palete3,Palete4,Palete5,Palete6) VALUES ('".$Y3."', '".$Y1."', '".$Y2."','".$linha1['Palete1']."','".$linha1['Palete2']."','".$linha1['Palete3']."','".$linha1['Palete4']."','".$linha1['Palete5']."','".$linha1['Palete6']."')";
            $result2 = mysqli_query($link,$sql) or die("A query falhou: " . mysqli_error());
            //Liberta o resultado 
            mysqli_free_result($result);
            // Fechando a conex„o
            mysqli_close($link);
            
            ?>


    <!-- Chamada do ficheiro .CSS com o estilo da pagina  -->
            <div class="cb">
                <?php
                echo $pagina1;
                echo $pagina2;
                echo $pagina9;
                
                ?>
            </div>
            <div class="cb2">
                <?php
                echo $pagina3;
                echo $pagina4;
                echo $pagina5;
                echo $pagina6;
                echo $pagina7;
                echo $pagina8;
                ?>
            </div>
            <div class="tab">
            <?php
               echo $palete;
               echo $destino;
                
                
            ?>
            </div>
        </div>
        <style> <?php include "./PSANEW.css" ; ?></style> 
    </body>
    
 </html>