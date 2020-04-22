FROM node:12.16.2

RUN mkdir -p /usr/src/app

WORKDIR /usr/src/app

COPY package.json ./

VOLUME ["/usr/src/app"]

RUN npm install

COPY . ./

EXPOSE 3000

CMD ["npm", "start"]