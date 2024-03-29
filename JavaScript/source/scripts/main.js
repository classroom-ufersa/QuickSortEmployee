import { Funcionario } from "./funcionario.js";

document.addEventListener('DOMContentLoaded', function () {
    const aquivoEnviado = document.getElementById('aquivoEnviado');
    const dadosDaTabela = document.getElementById('dadosDaTabela');
    const tbody = dadosDaTabela.querySelector('tbody');
    const form = document.getElementById('formTabela');
    const folhaSalarial = document.getElementById('folhaSalarial');
    const downloadButton = document.getElementById('downloadButton');
    const criarPlanilha = document.getElementById('criarPlanilha');
    const bemVindoSection = document.getElementById('bemVindo');
    const tabelaSection = document.getElementById('tabela');

    criarPlanilha.addEventListener('click', function () {

        const thead = document.createElement('thead');

        const tr = document.createElement('tr');

        const dadosColuna = ['Nome', 'Cargo', 'Salário'];

        for (const dadoColuna of dadosColuna) {

            const th = document.createElement('th');

            th.textContent = dadoColuna;

            tr.appendChild(th);
        }


        thead.appendChild(tr);

        dadosDaTabela.appendChild(thead);

        const planilhaVazia = XLSX.utils.aoa_to_sheet([dadosColuna]);

        const areaVazia = XLSX.utils.book_new();

        XLSX.utils.book_append_sheet(areaVazia, planilhaVazia, 'Planilha Vazia');

        const planilhaVaziaBlob = new Blob([s2ab(XLSX.write(areaVazia, { bookType: 'xlsx', type: 'binary' }))], {
            type: 'application/octet-stream'
        });

        bemVindoSection.style.display = 'none';

        tabelaSection.style.display = 'block';

        dadosDaTabela.style.display = 'table';
    });

    aquivoEnviado.addEventListener('change', function (event) {
        const file = event.target.files[0];
        if (file) {
            const reader = new FileReader();
            reader.onload = function (e) {
                const data = new Uint8Array(e.target.result);
                const workbook = XLSX.read(data, { type: 'array' });
                const sheetName = workbook.SheetNames[0];
                const sheet = workbook.Sheets[sheetName];
                const sheetData = XLSX.utils.sheet_to_json(sheet, { header: 1 });
    
                preencheTabela(sheetData);
                quickSort();
                bemVindoSection.style.display = 'none';
                tabelaSection.style.display = 'block';
            };
            reader.readAsArrayBuffer(file);
        }
    });
    

    form.addEventListener('submit', function (event) {
        event.preventDefault();
        const name = document.getElementById('name').value;
        const cargo = document.getElementById('cargo').value;
        const salario = document.getElementById('salario').value;

        if (name && cargo && salario) {
            const novoFuncionario = new Funcionario(name, cargo, salario);
            adicionarLinhaNaTabela(novoFuncionario, true); 
            quickSort();
            form.reset();
        } else {
            alert('Preencha todos os campos do formulário.');
        }
    });

    downloadButton.addEventListener('click', function () {
        const dadosCabecalho = [];
        const cabecalhoLinha = dadosDaTabela.querySelector('thead tr');
        for (const celula of cabecalhoLinha.cells) {
            dadosCabecalho.push(celula.textContent);
        }
    
        const conteudoLinha = [];
        const linhas = dadosDaTabela.querySelectorAll('tbody tr');
        for (const row of linhas) {
            const conteudoLinhaCelula = [];
            
            for (let i = 0; i < row.cells.length - 2; i++) {
                conteudoLinhaCelula.push(row.cells[i].textContent);
            }
            
            conteudoLinha.push(conteudoLinhaCelula);
        }
    
        const conteudo = [dadosCabecalho, ...conteudoLinha];
        const planilha = XLSX.utils.aoa_to_sheet(conteudo);
        const workbook = XLSX.utils.book_new();
        XLSX.utils.book_append_sheet(workbook, planilha, 'Tabela');
    
        const wbout = XLSX.write(workbook, { bookType: 'xlsx', type: 'binary' });
    
        function s2ab(s) {
            const buf = new ArrayBuffer(s.length);
            const view = new Uint8Array(buf);
            for (let i = 0; i !== s.length; ++i) {
                view[i] = s.charCodeAt(i) & 0xFF;
            }
            return buf;
        }
    
        const blob = new Blob([s2ab(wbout)], { type: 'application/octet-stream' });
    
        const planilhaDowload = document.createElement('a');
        planilhaDowload.href = URL.createObjectURL(blob);
        planilhaDowload.download = 'Funcionarios.xlsx';
        planilhaDowload.click();
    });

    function adicionarLinhaNaTabela(funcionario) {
        const tr = document.createElement('tr');
        const celulas = [funcionario.nome, funcionario.cargo, funcionario.salario];

        for (const conteudoCelula of celulas) {
            const td = document.createElement('td');
            td.textContent = conteudoCelula;
            tr.appendChild(td);
        }

        const editarDados = document.createElement('td');
        editarDados.classList.add('tamanho');
        const editButton = document.createElement('button');
        editButton.innerHTML = '<i class="bi bi-pencil-square p-0"></i>';
        editButton.addEventListener('click', function () {
            editarLinhas(tr);
        });
        editarDados.appendChild(editButton);
        tr.appendChild(editarDados);
    
        const deletarDados = document.createElement('td');
        deletarDados.classList.add('tamanho');
        const deleteButton = document.createElement('button');
        deleteButton.innerHTML = '<i class="bi bi-trash btn p-0"></i>';
        deleteButton.addEventListener('click', function () {
            deletaLinha(tr); // Chama a função para deletar a linha
        });
        deletarDados.appendChild(deleteButton);
        tr.appendChild(deletarDados);
    
        tbody.appendChild(tr);
        atualizaTotalFuncionarios();
        const totalSalario = calculaTotalSalario();
        folhaSalarial.querySelector('h2').textContent = `${totalSalario}`;
    }

    function editarLinhas(linha) {
        const celulas = linha.querySelectorAll('td');
        const form = document.getElementById('formTabela');

        form.elements['name'].value = celulas[0].textContent; 
        form.elements['cargo'].value = celulas[1].textContent; 
        form.elements['salario'].value = celulas[2].textContent; 

        linha.remove();
        atualizaTotalFuncionarios();
    }
    
    function deletaLinha(linha) {
        linha.remove();
        
        const celualaSalarios = tbody.querySelectorAll('tr td:nth-child(3)');
        let totalSalario = 0;
    
        celualaSalarios.forEach(cell => {
            const celulaSalarioValor = parseFloat(cell.textContent.replace('R$', '').replace(/\./g, '').replace(',', '.').trim());
            totalSalario += celulaSalarioValor;
        });
    
        folhaSalarial.querySelector('h2').textContent = formataSalario(totalSalario);
        atualizaTotalFuncionarios();
    }
    
    function preencheTabela(data) {
        const thead = document.createElement('thead');
        const thRow = document.createElement('tr');
        const dadosColuna = ['Nome', 'Cargo', 'Salário'];
    
        for (const dadoColuna of dadosColuna) {
            const th = document.createElement('th');
            th.textContent = dadoColuna;
            thRow.appendChild(th);
        }
    
        thead.appendChild(thRow);
        dadosDaTabela.appendChild(thead);
    
        for (let i = 0; i < data.length; i++) {
            if (i !== 0) {
                const funcionario = new Funcionario(data[i][0], data[i][1], data[i][2]);
                adicionarLinhaNaTabela(funcionario);
            }
        }
    
        dadosDaTabela.style.display = 'table';
    }  
    
    function quickSort() {
    const linhas = Array.from(tbody.querySelectorAll('tr'));
    linhas.sort((a, b) => a.cells[0].textContent.localeCompare(b.cells[0].textContent));
        
    for (let row of linhas) {
        tbody.appendChild(row);
    }

     // Formatar coluna de salário
     const celualaSalarios = tbody.querySelectorAll('tr td:nth-child(3)'); 
     celualaSalarios.forEach(cell => {
        const valorSalario = parseFloat(cell.textContent.replace('R$', '').replace('.', '').replace(',', '.').trim());
        cell.textContent = formataSalario(valorSalario);
    });    
        
    for (let row of linhas) {
        const celulaSalario = row.cells[2]; 

        if (!celulaSalario.textContent.startsWith('R$')) {
            const valorSalario = celulaSalario.textContent;
            celulaSalario.textContent = `R$ ${valorSalario}`;
        }
    }
    }
         
    function totalFuncionarios() {
        const linhas = tbody.querySelectorAll('tr'); 
        const totalFuncionarios = linhas.length; 
        return totalFuncionarios;
    }

    function atualizaTotalFuncionarios() {
        const totalFuncionariosAtualizado = totalFuncionarios();
        document.getElementById('totalFuncionarios').textContent = totalFuncionariosAtualizado;
    }

    function formataSalario(value) {
        return value.toLocaleString('pt-BR', { style: 'currency', currency: 'BRL' });
    }

    function calculaTotalSalario() {
        let totalSalario = 0;
    
        const celulaSalarios = tbody.querySelectorAll('tr td:nth-child(3)');
        celulaSalarios.forEach(cell => {
            const valorSalario = parseFloat(cell.textContent.replace('R$', '').replace('.', '').replace(',', '.').trim());
            totalSalario += valorSalario;
        });
    
        return formataSalario(totalSalario);
    }

    function s2ab(s) {
        const buf = new ArrayBuffer(s.length);
        const view = new Uint8Array(buf);
        for (let i = 0; i < s.length; ++i) {
            view[i] = s.charCodeAt(i) & 0xFF;
        }
        return buf;
    }
    
    $(document).ready(function () {
        $('#salario').maskMoney({
            thousands: '.',
            decimal: ',',
            affixesStay: false
        });
    });

    
});
