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
        
        <div class="linha">
    
            <img src="linha2.png" alt="LINHA DE TRANFERÊNCIA" style="width:400px;heigth:75px;margin-top:-50px;margin-left:-10px;" >

        </div>
    
    <!-- Forms para atualizaçao da página  -->
        <form action="PSANEW2.php" style= "text-align:center;"  method= "POST"> Ordem <br>       
        
        <label id= "palete"> Palete </label>  
        <input type="text" name="Palete" id="PALETE" value=0  placeholder="Numero da palete" >
        <label id= "destino"> Destino </label>          
        <input type="text" name="Destino"  id="DESTINO" value=0 placeholder="Barragem de destino" ><br>
        <input type="submit" name="mover" id="mover">
        </form>
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
        
        echo "Palete: ".$linha1['Palete'];
        echo " Destino: ".$linha1['Posicao']; 
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
        
      

// Criação e atribuição de valores as checkbox 
        if($linha1['Distribuicao']==1){
        echo " <br><input type='checkbox' name='Destino' value='checked'  style='margin-left:350px;' checked > ";
        } else { 
            echo "<br><input type='checkbox' name='Destino' value='checked'  style='margin-left:350px;'>  ";
        }
        if($linha1['Aguardar']==1){
            echo " <input type='checkbox'  value='checked'  style='margin-left:350px;margin-top:14px;' checked > ";
        } else { 
                echo "<input type='checkbox'  value='checked'  style='margin-left:350px;margin-top:14px;' >  ";
        }
        if($linha1['X1']==1){
            echo " <br><input type='checkbox'  value='checked'  style='margin-left:-470px;margin-top:-260px;' checked > ";
        } else { 
                echo " <br><input type='checkbox' value='checked' style='margin-left:-470px;margin-top:-260px;'> ";
        }
        if($linha1['X2']==1){
                echo " <br><input type='checkbox'  value='checked'  style='margin-left:-260px;margin-top:-30px;' checked > ";
        } else { 
                    echo " <br><input type='checkbox' value='checked' style='margin-left:-260px;margin-top:-30px;'> ";
        }
        if($linha1['X3']==1){
                    echo " <br><input type='checkbox'  value='checked' style='margin-left:-50px;margin-top:10px;'  checked > ";
        } else { 
                        echo " <br><input type='checkbox' value='checked' style='margin-left:-50px;margin-top:10px;'> ";
        }
        if($linha1['X4']==1){
            echo " <br><input type='checkbox'  value='checked' style='margin-left:-45px;margin-top:0px;'  checked > ";
        } else { 
                echo " <br><input type='checkbox' value='checked'style='margin-left:-45px;margin-top:0px;' > ";
        }
        if($linha1['X5']==1){
            echo " <br><input type='checkbox'  value='checked' style='margin-left:-300px;margin-top:-55px;'  checked > ";
        } else { 
                echo " <br><input type='checkbox' value='checked'style='margin-left:-300px;margin-top:-55px;' > ";
        }
        if($linha1['X6']==1){
            echo " <br><input type='checkbox'  value='checked'  style='margin-left:-510px;margin-top:-90px;' checked > ";
        } else { 
                echo " <br><input type='checkbox' value='checked'style='margin-left:-510px;margin-top:-90px;' > ";
        }
        if($linha1['Operacao']==1){
                echo " <input type='checkbox'  value='checked'   style='margin-left:350px;margin-top:190px;' checked > ";
        } else { 
                echo "<input type='checkbox'  value='checked'   style='margin-left:350px;margin-top:190px;' >  ";
        }
        
        //Liberta o resultado 
        mysqli_free_result($result);
         // Fechando a conex„o
         mysqli_close($link);
         
        ?>
<!-- Chamada do ficheiro .CSS com o estilo da pagina  -->
        <style> <?php include "./PSANEW.css" ; ?></style> 
        
        </div>
    </body>
 </html>