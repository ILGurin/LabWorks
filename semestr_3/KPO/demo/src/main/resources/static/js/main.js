const list = document.querySelector('#list')
const filter = document.querySelector('#filter')
const table = document.querySelector('#table')
const retirementButton = document.querySelector('#retirement')
const experienceButton = document.querySelector('#experience')
const allButton = document.querySelector('#all')

const isAdmin = document.querySelector('#isAdminDiv')
let isAdminBoolean = false
if(isAdmin == null){
    isAdminBoolean = false;
}else{
     isAdminBoolean = Boolean(isAdmin.getAttribute("data-message"))
}


let USERS = []
let employeesOfRetirementAge = []
let sortedEmployees = []
let currentDate = new Date();
let date
console.log(isAdminBoolean)


const newList = employyes.map(obj => ({
     ...obj, 
     experience: currentDate.getFullYear() - new Date((obj.startDate).replace(/(\d+).(\d+).(\d+)/, '$3/$2/$1')).getFullYear(),
     years: currentDate.getFullYear() - new Date((obj.dataOfBirth).replace(/(\d+).(\d+).(\d+)/, '$3/$2/$1')).getFullYear()}));

console.log(newList)


filter.addEventListener('input', (event) => {
    const { value } = event.target
    const filteredEmployees = newList.filter((newList) => {
        return newList.surname.toLowerCase().includes(value) //employee
    })
    if(value != null){
        render(filteredEmployees)

    }
})

retirementButton.addEventListener('click', (event) => {
    const filteredEmployees = newList.filter(employee => employee.years >= 60)
    render(filteredEmployees)
} )

experienceButton.addEventListener('click', (event) => {
    experienceList = newList.slice()
    experienceList.sort((a, b) => b.experience - a.experience)
    render(experienceList)
})

allButton.addEventListener('click', (event) => {
    render(newList)
})

async function start(){
    try{
        setTimeout(() => {
            USERS = newList //employee
            render(newList)
        }, 1000)
    }catch(err){
        list.style.color = 'reda'
        list.innerHTML = err.message
    }
}


function render(users = []){
    if(users.length === 0){
        table.innerHTML = 'No matched users!' //list
    }
    else{
        const html = users.map(toHTML).join('')
        table.innerHTML = html
    }

}

function toHTML(user){
    if(isAdminBoolean){
        return `
            <tr>
                <th scope="row">${user.id}</th>
                <td>${user.surname}</td>
                <td>${user.name}</td>
                <td>${user.patronymic}</td>
                <td>${user.dataOfBirth}</td>
                <td>${user.departmentName}</td>
                <td>${user.position}</td>
                <td>${user.startDate}</td>
                <td>${user.experience}</td>
                <td>${user.years}</td>
                <td><a href="/main/${user.id}">edit</a></td>
            </tr>
        `
    }else{
    return `
                <tr>
                    <th scope="row">${user.id}</th>
                    <td>${user.surname}</td>
                    <td>${user.name}</td>
                    <td>${user.patronymic}</td>
                    <td>${user.dataOfBirth}</td>
                    <td>${user.departmentName}</td>
                    <td>${user.position}</td>
                    <td>${user.startDate}</td>
                    <td>${user.experience}</td>
                    <td>${user.years}</td>
                </tr>
            `
    }
}
start()